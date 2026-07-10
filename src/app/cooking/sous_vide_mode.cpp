#include "app/cooking/sous_vide_mode.h"

#include <cmath>

namespace culina::app {

SousVideMode::SousVideMode(DeciCelsius target, std::uint32_t duration_s)
    : target_deci_(target), duration_ms_(duration_s * 1000u) {
    if (target_deci_ < 370) {
        target_deci_ = 370;
    }
    if (target_deci_ > 900) {
        target_deci_ = 900;
    }
}

void SousVideMode::on_tick(ProgramContext& ctx) {
    if (!heater_set_) {
        heater_set_ = ctx.mcu->set_heater(target_deci_) == Status::Ok;
        return;
    }
    if (!motor_set_) {
        motor_set_ = ctx.mcu->set_motor(dial_to_rpm(2), c1link::kRampGentle) == Status::Ok;
        return;
    }
    const float bath = ctx.telemetry->average_temp_c(2000);
    if (std::fabs(bath - to_celsius(target_deci_)) <= 0.5f) {
        at_temperature_ = true;
    }
}

} // namespace culina::app
