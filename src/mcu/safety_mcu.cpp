#include "mcu/safety_mcu.h"

#include "mcu/safety_limits.h"

namespace culina::mcu {

using namespace c1link;

SafetyMcu::SafetyMcu(const Hardware& hw, hal::IUart* uart, const hal::IClock* clock)
    : hw_(hw), clock_(clock), link_(uart, clock), motor_ctrl_(hw.motor),
      handler_(&link_, &motor_ctrl_, &pid_, &interlocks_, hw.scale, hw.lid),
      telemetry_(&link_, clock), last_valid_frame_ms_(clock->now_ms()) {}

bool SafetyMcu::sample_inputs() {
    const auto reading = hw_.temp_sensor->read_deci_celsius();
    temp_sensor_ok_ = reading.is_ok();
    if (!temp_sensor_ok_) {
        return false;
    }
    inputs_.temp_c = to_celsius(reading.value());
    inputs_.rpm = hw_.motor->rpm();
    inputs_.lid_closed = hw_.lid->is_closed();
    inputs_.lid_locked = hw_.lid->is_locked();
    inputs_.motor_stalled = hw_.motor->stalled();
    return true;
}

void SafetyMcu::enter_fault(FaultCode code) {
    fault_ = code;
    motor_ctrl_.stop();
    pid_.disable();
    hw_.heater->set_power_w(0.0f);
    telemetry_.publish_fault(code);
}

bool SafetyMcu::can_clear_fault() const {
    switch (fault_) {
    case FaultCode::None:
    case FaultCode::LinkLost:
        return true;
    case FaultCode::MotorStall:
        return true;
    case FaultCode::SensorFailure:
        return temp_sensor_ok_;
    case FaultCode::Overtemp:
        return inputs_.temp_c < limits::kOvertempCutoffC;
    }
    return false;
}

void SafetyMcu::tick_1ms() {
    ++tick_count_;

    if (!sample_inputs() && fault_ != FaultCode::SensorFailure) {
        enter_fault(FaultCode::SensorFailure);
    }

    // Always run control logic so a stalled sender cannot block interlocks.
    Frame frame;
    while (link_.poll(&frame)) {
        if (frame.type == FrameType::Request) {
            last_valid_frame_ms_ = clock_->now_ms();
        }
        handler_.handle(frame, inputs_, fault_ != FaultCode::None);
        if (frame.type == FrameType::Request && frame.msg_id == MsgId::MotorStop &&
            frame.payload_len == 0 && can_clear_fault()) {
            fault_ = FaultCode::None;
        }
    }

    if (fault_ == FaultCode::None) {
        const FaultCode tripped = interlocks_.evaluate(inputs_);
        if (tripped != FaultCode::None) {
            enter_fault(tripped);
        }
    }

    if (fault_ == FaultCode::None && (motor_ctrl_.active() || pid_.enabled()) &&
        clock_->now_ms() - last_valid_frame_ms_ >= limits::kLinkTimeoutMs) {
        enter_fault(FaultCode::LinkLost);
    }

    motor_ctrl_.enforce_cap(interlocks_.continuous_cap(inputs_));

    float watts = 0.0f;
    if (fault_ == FaultCode::None && pid_.enabled() && inputs_.lid_closed) {
        // Pause PID updates with the lid open to prevent integral windup.
        watts = pid_.update(inputs_.temp_c, 0.001f);
    }
    hw_.heater->set_power_w(watts);

    motor_ctrl_.tick_1ms();

    TelemetryData data;
    data.tick = tick_count_;
    data.deci_celsius = from_celsius(inputs_.temp_c);
    data.rpm = inputs_.rpm;
    data.grams = handler_.current_grams();
    data.flags = static_cast<std::uint8_t>(
        (inputs_.lid_closed ? kFlagLidClosed : 0) | (inputs_.lid_locked ? kFlagLidLocked : 0) |
        (watts > 0.0f ? kFlagHeaterOn : 0) | (inputs_.motor_stalled ? kFlagMotorStalled : 0));
    telemetry_.maybe_publish(data);
}

} // namespace culina::mcu
