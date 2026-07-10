#include "mcu/telemetry_publisher.h"

namespace culina::mcu {

using namespace c1link;

void TelemetryPublisher::maybe_publish(const TelemetryData& data) {
    if (pending_fault_ != FaultCode::None) {
        const std::uint8_t payload[] = {static_cast<std::uint8_t>(pending_fault_)};
        if (link_->send(FrameType::Telemetry, seq_, MsgId::Fault, payload, sizeof(payload)) !=
            Status::Ok) {
            return;
        }
        ++seq_;
        pending_fault_ = FaultCode::None;
    }

    const Millis now = clock_->now_ms();
    if (now - last_publish_ms_ < kPeriodMs) {
        return;
    }
    std::uint8_t payload[kTelemetryPayloadSize];
    encode_telemetry(data, payload);
    if (link_->send(FrameType::Telemetry, seq_, MsgId::Telemetry, payload, sizeof(payload)) ==
        Status::Ok) {
        ++seq_;
        last_publish_ms_ = now;
    }
}

void TelemetryPublisher::publish_fault(FaultCode code) {
    pending_fault_ = code;
}

} // namespace culina::mcu
