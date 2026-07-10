#include "mcu/safety_mcu.h"

namespace culina::mcu {

using namespace c1link;

SafetyMcu::SafetyMcu(const Hardware& hw, hal::IUart* uart, const hal::IClock* clock)
    : hw_(hw), link_(uart, clock), motor_ctrl_(hw.motor),
      handler_(&link_, &motor_ctrl_, &pid_, &interlocks_, hw.scale, hw.lid),
      telemetry_(&link_, clock) {}

void SafetyMcu::sample_inputs() {
    const auto reading = hw_.temp_sensor->read_deci_celsius();
    if (reading.is_ok()) {
        inputs_.temp_c = to_celsius(reading.value());
    }
    inputs_.rpm = hw_.motor->rpm();
    inputs_.lid_closed = hw_.lid->is_closed();
    inputs_.lid_locked = hw_.lid->is_locked();
    inputs_.motor_stalled = hw_.motor->stalled();
}

void SafetyMcu::enter_fault(FaultCode code) {
    fault_ = code;
    motor_ctrl_.stop();
    pid_.disable();
    hw_.heater->set_power_w(0.0f);
    telemetry_.publish_fault(code);
}

void SafetyMcu::tick_1ms() {
    ++tick_count_;

    // Drain whatever arrived, then always run the control path: a slow or
    // hostile sender must never hold the interlocks hostage.
    Frame frame;
    while (link_.poll(&frame)) {
        handler_.handle(frame, inputs_);
        if (frame.msg_id == MsgId::MotorStop || frame.msg_id == MsgId::HeaterOff) {
            fault_ = FaultCode::None;
        }
    }

    sample_inputs();

    if (fault_ == FaultCode::None) {
        const FaultCode tripped = interlocks_.evaluate(inputs_);
        if (tripped != FaultCode::None) {
            enter_fault(tripped);
        }
    }

    motor_ctrl_.enforce_cap(interlocks_.continuous_cap(inputs_));

    float watts = 0.0f;
    if (fault_ == FaultCode::None && pid_.enabled()) {
        watts = pid_.update(inputs_.temp_c, 0.001f);
        if (!inputs_.lid_closed) {
            watts = 0.0f; // no heating with the lid open
        }
    }
    hw_.heater->set_power_w(watts);

    motor_ctrl_.tick_1ms();

    TelemetryData data;
    data.tick = tick_count_;
    data.deci_celsius = from_celsius(inputs_.temp_c);
    data.rpm = inputs_.rpm;
    data.grams = handler_.current_grams();
    data.flags = static_cast<std::uint8_t>((inputs_.lid_closed ? kFlagLidClosed : 0) |
                                           (inputs_.lid_locked ? kFlagLidLocked : 0) |
                                           (watts > 0.0f ? kFlagHeaterOn : 0) |
                                           (inputs_.motor_stalled ? kFlagMotorStalled : 0));
    telemetry_.maybe_publish(data);
}

} // namespace culina::mcu
