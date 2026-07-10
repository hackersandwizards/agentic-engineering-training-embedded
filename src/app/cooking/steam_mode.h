#pragma once

#include "app/cooking/program.h"

namespace culina::app {

// Rolling boil with a gentle stir. Pauses heating feedback to the display
// while the lid is open; the MCU independently cuts heater power then.
class SteamMode : public Program {
public:
    explicit SteamMode(std::uint32_t duration_s) : duration_ms_(duration_s * 1000u) {}

    const char* name() const override { return "steam"; }
    void on_tick(ProgramContext& ctx) override;
    bool finished(const ProgramContext& ctx) const override {
        return ctx.elapsed_ms >= duration_ms_;
    }
    void on_stop(ProgramContext&) override {}
    const char* status(const ProgramContext&) const override {
        return lid_open_ ? "paused (lid open)" : "steaming";
    }

private:
    Millis duration_ms_;
    bool heater_set_ = false;
    bool motor_set_ = false;
    bool lid_open_ = false;
};

} // namespace culina::app
