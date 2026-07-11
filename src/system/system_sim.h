#pragma once

#include "app/application_runtime.h"
#include "mcu/safety_mcu.h"
#include "sim/in_memory_transport.h"
#include "sim/sim_board.h"

namespace culina::system {

// The whole device in one process: simulated board, safety MCU, and the
// application firmware, advancing in lockstep.
class SystemSim {
public:
    explicit SystemSim(std::uint32_t seed = 42);

    // Advance simulated time. MCU ticks at 1 kHz, the app at 100 Hz.
    void step_ms(std::uint32_t ms);

    sim::SimBoard& board() { return board_; }
    app::TelemetryStore& store() { return app_.telemetry(); }
    app::McuClient& client() { return app_.client(); }
    app::CookingController& controller() { return app_.controller(); }
    app::RecipeLibrary& recipes() { return app_.recipes(); }
    app::OtaUpdater& ota() { return app_.ota(); }

    Millis now_ms() const { return board_.clock().now_ms(); }

private:
    mcu::SafetyMcu::Hardware hardware();

    sim::SimBoard board_;
    sim::InMemoryTransport transport_;
    mcu::SafetyMcu mcu_;
    app::ApplicationRuntime app_{&transport_.app_side(), &board_.clock(), &board_.app_watchdog()};
};

} // namespace culina::system
