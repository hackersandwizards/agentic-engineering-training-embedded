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
    if (!program) {
        return Status::InvalidArgument;
    }
    if (state_ == SessionState::Running || state_ == SessionState::Stopping ||
        (state_ == SessionState::Faulted && !shutdown_motor_done_)) {
        return Status::NotReady;
    }
    begin_shutdown(false);
    pending_program_ = std::move(program);
    start_after_shutdown_ = true;
    return Status::Ok;
}

void CookingController::begin(std::unique_ptr<Program> program) {
    program_ = std::move(program);
    started_ms_ = clock_->now_ms();
    shutdown_heater_sent_ = false;
    shutdown_heater_done_ = false;
    shutdown_motor_sent_ = false;
    shutdown_motor_done_ = false;
    fault_shutdown_ = false;
    start_after_shutdown_ = false;
    pending_program_.reset();
    mcu_->clear_fault();
    mcu_->clear_command_status();
    state_ = SessionState::Running;
}

void CookingController::stop() {
    if (state_ == SessionState::Stopping && start_after_shutdown_) {
        start_after_shutdown_ = false;
        pending_program_.reset();
    } else if (state_ != SessionState::Stopping && state_ != SessionState::Faulted) {
        begin_shutdown(false);
    }
}

void CookingController::begin_shutdown(bool faulted) {
    shutdown_heater_sent_ = false;
    shutdown_heater_done_ = false;
    shutdown_motor_sent_ = false;
    shutdown_motor_done_ = false;
    fault_shutdown_ = faulted;
    start_after_shutdown_ = false;
    pending_program_.reset();
    mcu_->clear_command_status();
    state_ = faulted ? SessionState::Faulted : SessionState::Stopping;
}

void CookingController::run_stopping_sequence(const c1link::Frame* response) {
    if (response != nullptr && response->type == c1link::FrameType::Response) {
        if (shutdown_heater_sent_ && !shutdown_heater_done_ &&
            response->msg_id == c1link::MsgId::HeaterOff) {
            shutdown_heater_done_ = true;
        } else if (shutdown_motor_sent_ && !shutdown_motor_done_ &&
                   response->msg_id == c1link::MsgId::MotorStop) {
            shutdown_motor_done_ = true;
        }
    }

    if (mcu_->last_command_status() != Status::Ok) {
        mcu_->clear_command_status();
        if (!shutdown_heater_done_) {
            shutdown_heater_sent_ = false;
        } else if (!shutdown_motor_done_) {
            shutdown_motor_sent_ = false;
        }
    }

    if (!shutdown_heater_done_) {
        if (!shutdown_heater_sent_ && !mcu_->awaiting_response()) {
            shutdown_heater_sent_ = mcu_->heater_off() == Status::Ok;
        }
        return;
    }
    if (!shutdown_motor_done_) {
        if (!shutdown_motor_sent_ && !mcu_->awaiting_response()) {
            shutdown_motor_sent_ = mcu_->motor_stop() == Status::Ok;
        }
        return;
    }
    if (start_after_shutdown_ && pending_program_ && !fault_shutdown_) {
        auto next = std::move(pending_program_);
        begin(std::move(next));
        return;
    }
    state_ = fault_shutdown_ ? SessionState::Faulted : SessionState::Done;
}

void CookingController::tick_10ms() {
    // SR-006 requires feeding before potentially long OTA work.
    watchdog_->feed();

    c1link::Frame response;
    const bool has_response = mcu_->take_response(&response);

    display_avg_temp_c_ = telemetry_->average_temp_c(2000);
    hot_bowl_ = telemetry_->max_temp_c(2000) > 60.0f;

    if (state_ != SessionState::Faulted && (mcu_->last_fault() != c1link::FaultCode::None ||
                                            mcu_->last_command_status() != Status::Ok)) {
        begin_shutdown(true);
    }

    if (ota_ != nullptr && ota_->busy()) {
        ota_->step();
    }

    if (state_ == SessionState::Running && program_) {
        ProgramContext ctx{mcu_, telemetry_, clock_->now_ms() - started_ms_};
        program_->on_tick(ctx);
        if (program_->finished(ctx)) {
            program_->on_stop(ctx);
            begin_shutdown(false);
        }
    } else if (state_ == SessionState::Stopping || state_ == SessionState::Faulted) {
        run_stopping_sequence(has_response ? &response : nullptr);
    }
}

} // namespace culina::app
