#include "sim/motor_model.h"

namespace culina::sim {

namespace {
constexpr float kMaxRpm = 10700.0f;
constexpr float kSpeedTauSeconds = 0.4f;
constexpr float kIdleCurrentMa = 150.0f;
constexpr float kCurrentPerRpmMa = 0.05f;
// Load beyond this collapses the motor. Water in a full bowl at top speed
// stays comfortably below; thick dough at high speed exceeds it.
constexpr float kStallLoadLimit = 9000.0f;
} // namespace

void MotorModel::set_duty(float duty) {
    if (duty < 0.0f) {
        duty = 0.0f;
    }
    if (duty > 1.0f) {
        duty = 1.0f;
    }
    duty_ = duty;
    if (duty_ == 0.0f) {
        stalled_ = false;
    }
}

void MotorModel::step(float dt_seconds, float contents_grams) {
    if (stalled_) {
        rpm_ = 0.0f;
        current_ma_ = 2500;
        return;
    }

    const float target = duty_ * kMaxRpm;
    rpm_ += (target - rpm_) * dt_seconds / kSpeedTauSeconds;

    const float load = (rpm_ / kMaxRpm) * viscosity_ * (500.0f + contents_grams);
    if (load > kStallLoadLimit) {
        stalled_ = true;
        rpm_ = 0.0f;
        current_ma_ = 2500;
        return;
    }

    current_ma_ = static_cast<std::uint16_t>(
        duty_ > 0.0f ? kIdleCurrentMa + kCurrentPerRpmMa * rpm_ + load * 0.1f : 0.0f);
}

} // namespace culina::sim
