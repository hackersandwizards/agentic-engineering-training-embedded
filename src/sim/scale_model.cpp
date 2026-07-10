#include "sim/scale_model.h"

namespace culina::sim {

namespace {
constexpr float kDriftGramsPerMinute = 0.05f;
constexpr float kMaxRpm = 10700.0f;
constexpr float kVibrationAmplitudeG = 25.0f;
} // namespace

ScaleModel::ScaleModel(std::uint32_t seed) : rng_(seed) {}

void ScaleModel::step(float dt_seconds, float motor_rpm) {
    drift_g_ += kDriftGramsPerMinute * dt_seconds / 60.0f;
    vibration_rpm_ = motor_rpm;
}

std::int32_t ScaleModel::read_raw_counts() {
    const float speed_ratio = vibration_rpm_ / kMaxRpm;
    const float vibration = kVibrationAmplitudeG * speed_ratio * speed_ratio * noise_(rng_);
    const float gauss = noise_(rng_);
    const float grams = true_mass_g_ + drift_g_ + gauss + vibration;
    return static_cast<std::int32_t>(grams * kCountsPerGram);
}

} // namespace culina::sim
