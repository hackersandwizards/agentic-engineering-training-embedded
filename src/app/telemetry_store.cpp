#include "app/telemetry_store.h"

namespace culina::app {

void TelemetryStore::append(const Sample& sample) {
    const std::scoped_lock lock(mutex_);
    samples_.push_back(sample);
    if (samples_.size() > kMaxSamples) {
        samples_.pop_front();
    }
}

TelemetryStore::Sample TelemetryStore::latest() const {
    const std::scoped_lock lock(mutex_);
    return samples_.empty() ? Sample{} : samples_.back();
}

bool TelemetryStore::has_data() const {
    const std::scoped_lock lock(mutex_);
    return !samples_.empty();
}

std::size_t TelemetryStore::size() const {
    const std::scoped_lock lock(mutex_);
    return samples_.size();
}

float TelemetryStore::average_temp_c(Millis window_ms) const {
    const std::scoped_lock lock(mutex_);
    if (samples_.empty()) {
        return 0.0f;
    }
    const Millis newest = samples_.back().t_ms;
    float sum = 0.0f;
    std::size_t count = 0;
    for (auto it = samples_.rbegin(); it != samples_.rend(); ++it) {
        if (newest - it->t_ms > window_ms) {
            break;
        }
        sum += to_celsius(it->deci_celsius);
        ++count;
    }
    return count > 0 ? sum / static_cast<float>(count) : 0.0f;
}

float TelemetryStore::max_temp_c(Millis window_ms) const {
    const std::scoped_lock lock(mutex_);
    if (samples_.empty()) {
        return 0.0f;
    }
    const Millis newest = samples_.back().t_ms;
    float max_c = -1000.0f;
    for (auto it = samples_.rbegin(); it != samples_.rend(); ++it) {
        if (newest - it->t_ms > window_ms) {
            break;
        }
        const float c = to_celsius(it->deci_celsius);
        if (c > max_c) {
            max_c = c;
        }
    }
    return max_c;
}

} // namespace culina::app
