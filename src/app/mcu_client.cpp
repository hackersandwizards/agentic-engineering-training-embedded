#include "app/mcu_client.h"

#include "common/logging.h"

#include <cstring>

namespace culina::app {

using namespace c1link;

void McuClient::poll() {
    if (waiting_ &&
        static_cast<std::int32_t>(clock_->now_ms() - sent_at_ms_ - kResponseTimeoutMs) > 0) {
        if (!retried_) {
            // One retry under a fresh sequence number.
            retried_ = true;
            sent_at_ms_ = clock_->now_ms();
            link_.send(FrameType::Request, next_seq_++, pending_msg_id_, pending_payload_,
                       pending_payload_len_);
        } else {
            CULINA_LOG_WARN("request 0x%02x timed out after retry",
                            static_cast<unsigned>(pending_msg_id_));
            waiting_ = false;
        }
    }

    Frame frame;
    while (link_.poll(&frame)) {
        if (frame.type == FrameType::Telemetry && frame.msg_id == MsgId::Telemetry &&
            frame.payload_len == kTelemetryPayloadSize) {
            TelemetryStore::Sample sample;
            sample.t_ms = clock_->now_ms();
            sample.deci_celsius = get_i16(frame.payload + 4);
            sample.rpm = get_u16(frame.payload + 6);
            sample.grams = get_i32(frame.payload + 8);
            sample.flags = frame.payload[12];
            store_->append(sample);
        } else if (frame.type == FrameType::Telemetry && frame.msg_id == MsgId::Fault &&
                   frame.payload_len == 1) {
            last_fault_ = static_cast<FaultCode>(frame.payload[0]);
        } else if (frame.type == FrameType::Response || frame.type == FrameType::Nack) {
            if (waiting_ && frame.msg_id == pending_msg_id_) {
                response_ = frame;
                response_ready_ = true;
                waiting_ = false;
            }
        }
    }
}

Status McuClient::request(MsgId id, const std::uint8_t* payload, std::uint16_t len) {
    if (waiting_) {
        return Status::NotReady;
    }
    if (len > kMaxPayload) {
        return Status::InvalidArgument;
    }
    const Status sent = link_.send(FrameType::Request, next_seq_++, id, payload, len);
    if (sent != Status::Ok) {
        return sent;
    }
    waiting_ = true;
    pending_msg_id_ = id;
    response_ready_ = false;
    sent_at_ms_ = clock_->now_ms();
    retried_ = false;
    if (len > 0) {
        std::memcpy(pending_payload_, payload, len);
    }
    pending_payload_len_ = len;
    return Status::Ok;
}

bool McuClient::take_response(Frame* out) {
    if (!response_ready_) {
        return false;
    }
    *out = response_;
    response_ready_ = false;
    return true;
}

Status McuClient::set_motor(Rpm rpm, std::uint8_t ramp_profile) {
    std::uint8_t payload[3];
    put_u16(payload, rpm);
    payload[2] = ramp_profile;
    return request(MsgId::MotorSetTarget, payload, sizeof(payload));
}

Status McuClient::motor_stop() { return request(MsgId::MotorStop, nullptr, 0); }

Status McuClient::set_heater(DeciCelsius target) {
    std::uint8_t payload[2];
    put_i16(payload, target);
    return request(MsgId::HeaterSetTarget, payload, sizeof(payload));
}

Status McuClient::heater_off() { return request(MsgId::HeaterOff, nullptr, 0); }

Status McuClient::tare() { return request(MsgId::ScaleTare, nullptr, 0); }

Status McuClient::lock_lid(bool locked) {
    return request(locked ? MsgId::LidLock : MsgId::LidUnlock, nullptr, 0);
}

} // namespace culina::app
