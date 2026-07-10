#pragma once

#include "hal/i_clock.h"
#include "protocol/link.h"

namespace culina::mcu {

// Streams device state to the application processor at a fixed rate.
class TelemetryPublisher {
public:
    TelemetryPublisher(c1link::Link* link, const hal::IClock* clock)
        : link_(link), clock_(clock) {}

    void maybe_publish(const c1link::TelemetryData& data);
    void publish_fault(c1link::FaultCode code);

    static constexpr Millis kPeriodMs = 10; // 100 Hz keeps the UI responsive

private:
    c1link::Link* link_;
    const hal::IClock* clock_;
    Millis last_publish_ms_ = 0;
    std::uint8_t seq_ = 0;
};

} // namespace culina::mcu
