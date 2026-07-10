#include "app/cooking/cooking_controller.h"

#include "app/cooking/guided_recipe.h"
#include "app/cooking/manual_mode.h"

namespace culina::app {

const char* session_state_name(SessionState state) {
    switch (state) {
    case SessionState::Idle:
        return "idle";
    case SessionState::Running:
        return "running";
    case SessionState::Stopping:
        return "stopping";
    case SessionState::Done:
        return "done";
    case SessionState::Faulted:
        return "FAULT";
    }
    return "?";
}

const char* CookingController::program_status() const {
    if (!program_) {
        return "-";
    }
    ProgramContext ctx{mcu_, telemetry_, clock_->now_ms() - started_ms_};
    return program_->status(ctx);
}

Status CookingController::start_manual(DeciCelsius temp, std::uint8_t dial,
                                       std::uint32_t duration_s) {
    return start_program(std::make_unique<ManualMode>(temp, dial, duration_s));
}

Status CookingController::start_recipe(const Recipe* recipe) {
    if (recipe == nullptr || recipe->step_count == 0) {
        return Status::InvalidArgument;
    }
    return start_program(std::make_unique<GuidedRecipe>(recipe));
}

Status CookingController::start_program(std::unique_ptr<Program> program) {
    if (state_ == SessionState::Running || state_ == SessionState::Stopping) {
        return Status::NotReady;
    }
    begin(std::move(program));
    return Status::Ok;
}

void CookingController::begin(std::unique_ptr<Program> program) {
    program_ = std::move(program);
    started_ms_ = clock_->now_ms();
    shutdown_heater_done_ = false;
    shutdown_motor_done_ = false;
    mcu_->clear_fault();
    state_ = SessionState::Running;
}

void CookingController::stop() {
    if (state_ == SessionState::Running) {
        state_ = SessionState::Stopping;
    }
}

void CookingController::run_stopping_sequence() {
    if (!shutdown_heater_done_) {
        shutdown_heater_done_ = mcu_->heater_off() == Status::Ok;
        return;
    }
    if (!shutdown_motor_done_) {
        shutdown_motor_done_ = mcu_->motor_stop() == Status::Ok;
        return;
    }
    state_ = SessionState::Done;
}

void CookingController::tick_10ms() {
    watchdog_->feed();

    c1link::Frame response;
    mcu_->take_response(&response);

    display_avg_temp_c_ = telemetry_->average_temp_c(2000);
    hot_bowl_ = telemetry_->max_temp_c(2000) > 60.0f;

    if (mcu_->last_fault() != c1link::FaultCode::None &&
        (state_ == SessionState::Running || state_ == SessionState::Stopping)) {
        state_ = SessionState::Faulted;
        return;
    }

    if (state_ == SessionState::Running && program_) {
        ProgramContext ctx{mcu_, telemetry_, clock_->now_ms() - started_ms_};
        program_->on_tick(ctx);
        if (program_->finished(ctx)) {
            program_->on_stop(ctx);
            state_ = SessionState::Stopping;
        }
    } else if (state_ == SessionState::Stopping) {
        run_stopping_sequence();
    }
}

} // namespace culina::app
