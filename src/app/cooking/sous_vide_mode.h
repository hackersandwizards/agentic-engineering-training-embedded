#pragma once

#include "app/cooking/program.h"

namespace culina::app {

// Long low-temperature hold. Target range 37.0-90.0 C, speed capped at
// dial 2 for gentle circulation.
class SousVideMode : public Program {
public:
    SousVideMode(DeciCelsius target, std::uint32_t duration_s);

    const char* name() const override { return "sous-vide"; }
    void on_tick(ProgramContext& ctx) override;
    bool finished(const ProgramContext& ctx) const override {
        return ctx.elapsed_ms >= duration_ms_;
    }
    void on_stop(ProgramContext&) override {}
    const char* status(const ProgramContext&) const override {
        return at_temperature_ ? "at temperature" : "heating";
    }

    bool at_temperature() const { return at_temperature_; }

private:
    DeciCelsius target_deci_;
    Millis duration_ms_;
    bool heater_set_ = false;
    bool motor_set_ = false;
    bool at_temperature_ = false;
};

} // namespace culina::app
