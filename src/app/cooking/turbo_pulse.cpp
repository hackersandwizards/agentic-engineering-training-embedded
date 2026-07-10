#include "app/cooking/turbo_pulse.h"

namespace culina::app {

void TurboPulse::on_tick(ProgramContext& ctx) {
    switch (phase_) {
    case Phase::Locking:
        if (ctx.mcu->lock_lid(true) == Status::Ok) {
            phase_ = Phase::Spinning;
        }
        break;
    case Phase::Spinning:
        if (spin_started_ms_ == 0) {
            if (ctx.mcu->set_motor(10700, c1link::kRampBurst) == Status::Ok) {
                spin_started_ms_ = ctx.elapsed_ms;
            }
        } else if (ctx.elapsed_ms - spin_started_ms_ >= pulse_ms_) {
            phase_ = Phase::Stopping;
        }
        break;
    case Phase::Stopping:
        if (ctx.mcu->motor_stop() == Status::Ok) {
            phase_ = Phase::Unlocking;
        }
        break;
    case Phase::Unlocking:
        if (!ctx.telemetry->has_data() || ctx.telemetry->latest().rpm >= 100) {
            break;
        }
        if (ctx.mcu->lock_lid(false) == Status::Ok) {
            phase_ = Phase::Finished;
        }
        break;
    case Phase::Finished:
        break;
    }
}

const char* TurboPulse::status(const ProgramContext&) const {
    switch (phase_) {
    case Phase::Locking:
        return "locking lid";
    case Phase::Spinning:
        return "pulse";
    case Phase::Stopping:
    case Phase::Unlocking:
        return "winding down";
    case Phase::Finished:
        return "done";
    }
    return "done";
}

} // namespace culina::app
