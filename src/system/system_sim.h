#pragma once

#include "app/cooking/cooking_controller.h"
#include "app/mcu_client.h"
#include "app/ota/ota_updater.h"
#include "app/recipe/recipe_library.h"
#include "app/telemetry_store.h"
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
    app::TelemetryStore& store() { return store_; }
    app::McuClient& client() { return client_; }
    app::CookingController& controller() { return controller_; }
    app::RecipeLibrary& recipes() { return recipes_; }
    app::OtaUpdater& ota() { return ota_; }

    Millis now_ms() const { return board_.clock().now_ms(); }

private:
    mcu::SafetyMcu::Hardware hardware();

    sim::SimBoard board_;
    sim::InMemoryTransport transport_;
    mcu::SafetyMcu mcu_;
    app::TelemetryStore store_;
    app::McuClient client_{&transport_.app_side(), &board_.clock(), &store_};
    app::CookingController controller_{&client_, &store_, &board_.clock(),
                                       &board_.app_watchdog()};
    app::RecipeLibrary recipes_;
    app::OtaUpdater ota_;
    std::uint32_t app_divider_ = 0;
};

} // namespace culina::system
