#include "app/cooking/manual_mode.h"

namespace culina::app {

void ManualMode::on_tick(ProgramContext& ctx) {
    if (!heater_set_) {
        heater_set_ = temp_deci_ <= 0 || ctx.mcu->set_heater(temp_deci_) == Status::Ok;
        return;
    }
    if (!motor_set_) {
        motor_set_ = ctx.mcu->set_motor(dial_to_rpm(dial_), c1link::kRampNormal) == Status::Ok;
    }
}

void ManualMode::on_stop(ProgramContext&) {}

} // namespace culina::app
