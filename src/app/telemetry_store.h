#pragma once

#include "common/time_types.h"
#include "common/units.h"

#include <cstddef>
#include <cstdint>
#include <mutex>
#include <vector>

namespace culina::app {

// History of device telemetry on the application processor. Feeds the status
// display, cooking logic, and post-run diagnostics.
class TelemetryStore {
public:
    struct Sample {
        Millis t_ms = 0;
        DeciCelsius deci_celsius = 0;
        Rpm rpm = 0;
        Grams grams = 0;
        std::uint8_t flags = 0;
    };

    void append(const Sample& sample);

    Sample latest() const;
    bool has_data() const;
    std::size_t size() const;

    // Mean temperature over the trailing window, ending at the newest sample.
    float average_temp_c(Millis window_ms) const;

    // Hottest reading in the trailing window; drives the spill-guard display.
    float max_temp_c(Millis window_ms) const;

private:
    // The link pump and the UI/controller read concurrently in two-process
    // mode; every accessor takes the lock.
    mutable std::mutex mutex_;
    std::vector<Sample> samples_;
};

} // namespace culina::app
