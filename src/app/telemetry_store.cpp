#include "app/telemetry_store.h"

namespace culina::app {

void TelemetryStore::append(const Sample& sample) { samples_.push_back(sample); }

TelemetryStore::Sample TelemetryStore::latest() const {
    return samples_.empty() ? Sample{} : samples_.back();
}

bool TelemetryStore::has_data() const { return !samples_.empty(); }

std::size_t TelemetryStore::size() const { return samples_.size(); }

float TelemetryStore::average_temp_c(Millis window_ms) const {
    if (samples_.empty()) {
        return 0.0f;
    }
    const Millis newest = samples_.back().t_ms;
    const Millis cutoff = window_ms >= newest ? 0 : newest - window_ms;
    float sum = 0.0f;
    std::size_t count = 0;
    for (const Sample& s : samples_) {
        if (s.t_ms >= cutoff) {
            sum += to_celsius(s.deci_celsius);
            ++count;
        }
    }
    return count > 0 ? sum / static_cast<float>(count) : 0.0f;
}

float TelemetryStore::max_temp_c(Millis window_ms) const {
    if (samples_.empty()) {
        return 0.0f;
    }
    const Millis newest = samples_.back().t_ms;
    const Millis cutoff = window_ms >= newest ? 0 : newest - window_ms;
    float max_c = -1000.0f;
    for (const Sample& s : samples_) {
        if (s.t_ms >= cutoff) {
            const float c = to_celsius(s.deci_celsius);
            if (c > max_c) {
                max_c = c;
            }
        }
    }
    return max_c;
}

} // namespace culina::app
