#include "app/cooking/guided_recipe.h"

namespace culina::app {

bool GuidedRecipe::run_setup(const RecipeStep& step, ProgramContext& ctx) {
    switch (step.kind) {
    case StepKind::Note:
        return true;
    case StepKind::Mix:
        return ctx.mcu->set_motor(dial_to_rpm(step.dial_speed), c1link::kRampNormal) == Status::Ok;
    case StepKind::Heat:
        if (command_index_ == 0) {
            if (ctx.mcu->set_heater(step.target_temp) == Status::Ok) {
                command_index_ = 1;
            }
            return false;
        }
        return ctx.mcu->set_motor(dial_to_rpm(step.dial_speed), c1link::kRampGentle) == Status::Ok;
    case StepKind::Weigh:
        if (scale_tared_) {
            return true;
        }
        scale_tared_ = ctx.mcu->tare() == Status::Ok;
        return scale_tared_;
    }
    return true;
}

bool GuidedRecipe::step_done(const RecipeStep& step, const ProgramContext& ctx) const {
    switch (step.kind) {
    case StepKind::Note:
        return advance_requested_;
    case StepKind::Mix:
    case StepKind::Heat:
        return ctx.elapsed_ms - step_started_ms_ >= step.duration_s * 1000u;
    case StepKind::Weigh:
        return ctx.telemetry->latest().grams >= step.target_weight;
    }
    return true;
}

bool GuidedRecipe::run_teardown(const RecipeStep& step, ProgramContext& ctx) {
    switch (step.kind) {
    case StepKind::Note:
    case StepKind::Weigh:
        return true;
    case StepKind::Mix:
        return ctx.mcu->motor_stop() == Status::Ok;
    case StepKind::Heat:
        if (command_index_ == 0) {
            if (ctx.mcu->heater_off() == Status::Ok) {
                command_index_ = 1;
            }
            return false;
        }
        return ctx.mcu->motor_stop() == Status::Ok;
    }
    return true;
}

void GuidedRecipe::advance() {
    ++step_index_;
    phase_ = Phase::Setup;
    command_index_ = 0;
    advance_requested_ = false;
}

void GuidedRecipe::on_tick(ProgramContext& ctx) {
    if (step_index_ >= recipe_->step_count) {
        return;
    }
    const RecipeStep& step = recipe_->steps[step_index_];
    switch (phase_) {
    case Phase::Setup:
        if (run_setup(step, ctx)) {
            step_started_ms_ = ctx.elapsed_ms;
            command_index_ = 0;
            phase_ = Phase::Run;
        }
        break;
    case Phase::Run:
        if (step_done(step, ctx)) {
            command_index_ = 0;
            phase_ = Phase::Teardown;
        }
        break;
    case Phase::Teardown:
        if (run_teardown(step, ctx)) {
            advance();
        }
        break;
    }
}

const char* GuidedRecipe::status(const ProgramContext&) const {
    if (step_index_ >= recipe_->step_count) {
        return "done";
    }
    const RecipeStep& step = recipe_->steps[step_index_];
    return step.text[0] != '\0' ? step.text : "working";
}

bool GuidedRecipe::awaiting_user() const {
    return phase_ == Phase::Run && step_index_ < recipe_->step_count &&
           recipe_->steps[step_index_].kind == StepKind::Note;
}

} // namespace culina::app
