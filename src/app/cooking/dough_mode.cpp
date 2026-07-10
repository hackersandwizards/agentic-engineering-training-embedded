#include "app/cooking/dough_mode.h"

namespace culina::app {

void DoughMode::on_tick(ProgramContext& ctx) {
    const Millis cycle = ctx.elapsed_ms % (kKneadMs + kRestMs);
    const bool want_knead = cycle < kKneadMs;
    if (want_knead != kneading_ || command_pending_) {
        const Rpm target = want_knead ? dial_to_rpm(3) : 0;
        if (ctx.mcu->set_motor(target, c1link::kRampFast) == Status::Ok) {
            kneading_ = want_knead;
            command_pending_ = false;
        } else {
            command_pending_ = true;
        }
    }
}

} // namespace culina::app
