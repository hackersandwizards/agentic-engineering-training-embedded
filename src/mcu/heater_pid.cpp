#include "mcu/heater_pid.h"

#include <cmath>

namespace culina::mcu {

namespace {
constexpr float kKp = 130.0f;
constexpr float kKi = 2.0f;
constexpr float kMaxWatts = 1200.0f;
// Limit integration to avoid windup during initial heating.
constexpr float kIntegralBandC = 5.0f;
} // namespace

void HeaterPid::set_target(DeciCelsius target) {
    if (!enabled_ || target != target_deci_) {
        integral_ = 0.0f;
    }
    target_deci_ = target;
    enabled_ = true;
}

void HeaterPid::disable() {
    enabled_ = false;
    target_deci_ = 0;
    integral_ = 0.0f;
}

float HeaterPid::update(float measured_c, float dt_seconds) {
    if (!enabled_) {
        return 0.0f;
    }
    const float error = to_celsius(target_deci_) - measured_c;
    if (std::fabs(error) < kIntegralBandC) {
        integral_ += error * dt_seconds;
    }
    float watts = kKp * error + kKi * integral_;
    if (watts < 0.0f) {
        watts = 0.0f;
    }
    if (watts > kMaxWatts) {
        watts = kMaxWatts;
    }
    return watts;
}

} // namespace culina::mcu
