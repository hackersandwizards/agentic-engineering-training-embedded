#pragma once

#include "app/cooking/program.h"

namespace culina::app {

// Full-power chopping burst. Locks the lid, spins to maximum for the pulse
// duration, then releases everything.
class TurboPulse : public Program {
public:
    explicit TurboPulse(std::uint32_t pulse_ms) : pulse_ms_(pulse_ms > 2000 ? 2000 : pulse_ms) {}

    const char* name() const override { return "turbo"; }
    void on_tick(ProgramContext& ctx) override;
    bool finished(const ProgramContext&) const override { return phase_ == Phase::Finished; }
    void on_stop(ProgramContext&) override {}
    const char* status(const ProgramContext&) const override;

private:
    enum class Phase { Locking, Spinning, Stopping, Unlocking, Finished };

    Millis pulse_ms_;
    Phase phase_ = Phase::Locking;
    Millis spin_started_ms_ = 0;
};

} // namespace culina::app
