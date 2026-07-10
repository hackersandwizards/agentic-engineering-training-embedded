#pragma once

#include "app/cooking/program.h"

namespace culina::app {

// Interval kneading: bursts of speed 3 with rest phases so the dough relaxes.
// No heat.
class DoughMode : public Program {
public:
    explicit DoughMode(std::uint32_t duration_s) : duration_ms_(duration_s * 1000u) {}

    const char* name() const override { return "dough"; }
    void on_tick(ProgramContext& ctx) override;
    bool finished(const ProgramContext& ctx) const override {
        return ctx.elapsed_ms >= duration_ms_;
    }
    void on_stop(ProgramContext&) override {}
    const char* status(const ProgramContext&) const override {
        return kneading_ ? "kneading" : "resting";
    }

    static constexpr Millis kKneadMs = 4000;
    static constexpr Millis kRestMs = 2000;

private:
    Millis duration_ms_;
    bool kneading_ = false;
    bool command_pending_ = true;
};

} // namespace culina::app
