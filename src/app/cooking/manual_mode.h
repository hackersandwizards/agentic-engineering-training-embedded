#pragma once

#include "app/cooking/program.h"

namespace culina::app {

// Direct temperature/speed/time control, like turning the dials by hand.
class ManualMode : public Program {
public:
    ManualMode(DeciCelsius temp, std::uint8_t dial, std::uint32_t duration_s)
        : temp_deci_(temp), dial_(dial), duration_ms_(duration_s * 1000u) {}

    const char* name() const override { return "manual"; }
    void on_tick(ProgramContext& ctx) override;
    bool finished(const ProgramContext& ctx) const override {
        return ctx.elapsed_ms >= duration_ms_;
    }
    void on_stop(ProgramContext& ctx) override;
    const char* status(const ProgramContext&) const override { return "running"; }

private:
    DeciCelsius temp_deci_;
    std::uint8_t dial_;
    Millis duration_ms_;
    bool heater_set_ = false;
    bool motor_set_ = false;
};

} // namespace culina::app
