#include "sim/sim_board.h"

namespace culina::sim {

SimBoard::SimBoard(std::uint32_t seed) : scale_model_(seed), temp_hal_(&thermal_model_, seed + 1) {}

void SimBoard::step_ms(std::uint32_t ms) {
    constexpr float kDtSeconds = 0.001f;
    for (std::uint32_t i = 0; i < ms; ++i) {
        clock_.advance_us(1000);
        motor_model_.step(kDtSeconds, scale_model_.true_mass_g());
        scale_model_.step(kDtSeconds, static_cast<float>(motor_model_.rpm()));
        thermal_model_.step(kDtSeconds, heater_hal_.power_w(), scale_model_.true_mass_g());
        watchdog_.check();
    }
}

} // namespace culina::sim
