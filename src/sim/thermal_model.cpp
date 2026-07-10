#include "sim/thermal_model.h"

namespace culina::sim {

namespace {
constexpr float kBowlHeatCapacityJPerK = 500.0f;
constexpr float kContentsHeatCapacityJPerGK = 4.18f;
constexpr float kLossWPerK = 5.0f;
} // namespace

void ThermalModel::step(float dt_seconds, float heater_watts, float contents_grams) {
    const float capacity = kBowlHeatCapacityJPerK + kContentsHeatCapacityJPerGK * contents_grams;
    const float loss_watts = kLossWPerK * (temperature_c_ - ambient_c_);
    temperature_c_ += (heater_watts - loss_watts) * dt_seconds / capacity;
    if (temperature_c_ < ambient_c_ - 40.0f) {
        temperature_c_ = ambient_c_ - 40.0f;
    }
}

void ThermalModel::set_ambient_c(float celsius) {
    ambient_c_ = celsius;
}

} // namespace culina::sim
