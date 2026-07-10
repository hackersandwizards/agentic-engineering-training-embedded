#include "app/cooking/steam_mode.h"

namespace culina::app {

void SteamMode::on_tick(ProgramContext& ctx) {
    if (!heater_set_) {
        heater_set_ = ctx.mcu->set_heater(1000) == Status::Ok;
        return;
    }
    if (!motor_set_) {
        motor_set_ = ctx.mcu->set_motor(dial_to_rpm(1), c1link::kRampGentle) == Status::Ok;
        return;
    }
    lid_open_ = (ctx.telemetry->latest().flags & c1link::kFlagLidClosed) == 0;
}

} // namespace culina::app
