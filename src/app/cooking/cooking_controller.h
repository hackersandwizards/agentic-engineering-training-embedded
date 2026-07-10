#pragma once

#include "app/cooking/program.h"
#include "app/ota/ota_updater.h"
#include "app/recipe/recipe.h"
#include "hal/i_clock.h"
#include "hal/i_watchdog.h"

#include <memory>

namespace culina::app {

enum class SessionState { Idle, Running, Stopping, Done, Faulted };

const char* session_state_name(SessionState state);

// Owns the cooking session on the application processor. Ticks at 100 Hz:
// feeds the watchdog, refreshes display metrics, and advances the active
// program.
class CookingController {
public:
    CookingController(McuClient* mcu, TelemetryStore* telemetry, const hal::IClock* clock,
                      hal::IWatchdog* watchdog)
        : mcu_(mcu), telemetry_(telemetry), clock_(clock), watchdog_(watchdog) {}

    void tick_10ms();

    void attach_ota(OtaUpdater* ota) { ota_ = ota; }

    Status start_manual(DeciCelsius temp, std::uint8_t dial, std::uint32_t duration_s);
    Status start_program(std::unique_ptr<Program> program);
    Status start_recipe(const Recipe* recipe);
    void stop();

    bool awaiting_user() const { return program_ && program_->awaiting_user(); }
    void user_next() {
        if (program_) {
            program_->user_next();
        }
    }

    SessionState state() const { return state_; }
    const char* program_name() const { return program_ ? program_->name() : "-"; }
    const char* program_status() const;

    // Display metrics, refreshed every tick.
    float display_avg_temp_c() const { return display_avg_temp_c_; }
    bool hot_bowl() const { return hot_bowl_; }

private:
    void begin(std::unique_ptr<Program> program);
    void run_stopping_sequence();

    McuClient* mcu_;
    TelemetryStore* telemetry_;
    const hal::IClock* clock_;
    hal::IWatchdog* watchdog_;

    OtaUpdater* ota_ = nullptr;
    SessionState state_ = SessionState::Idle;
    std::unique_ptr<Program> program_;
    Millis started_ms_ = 0;
    float display_avg_temp_c_ = 0.0f;
    bool hot_bowl_ = false;
    bool shutdown_heater_done_ = false;
    bool shutdown_motor_done_ = false;
};

} // namespace culina::app
