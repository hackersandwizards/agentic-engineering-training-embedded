#include "mcu/telemetry_publisher.h"

namespace culina::mcu {

using namespace c1link;

void TelemetryPublisher::maybe_publish(const TelemetryData& data) {
    const Millis now = clock_->now_ms();
    if (now - last_publish_ms_ < kPeriodMs) {
        return;
    }
    last_publish_ms_ = now;
    std::uint8_t payload[kTelemetryPayloadSize];
    encode_telemetry(data, payload);
    link_->send(FrameType::Telemetry, seq_++, MsgId::Telemetry, payload, sizeof(payload));
}

void TelemetryPublisher::publish_fault(FaultCode code) {
    const std::uint8_t payload[] = {static_cast<std::uint8_t>(code)};
    link_->send(FrameType::Telemetry, seq_++, MsgId::Fault, payload, sizeof(payload));
}

} // namespace culina::mcu
