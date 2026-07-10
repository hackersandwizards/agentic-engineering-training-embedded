#pragma once

#include "app/cooking/program.h"
#include "app/recipe/recipe.h"

namespace culina::app {

// Walks a recipe step by step: notes wait for the user, weigh steps wait for
// the target weight on the scale, mix and heat steps run on a timer.
class GuidedRecipe : public Program {
public:
    explicit GuidedRecipe(const Recipe* recipe) : recipe_(recipe) {}

    const char* name() const override { return recipe_->name; }
    void on_tick(ProgramContext& ctx) override;
    bool finished(const ProgramContext&) const override {
        return step_index_ >= recipe_->step_count;
    }
    void on_stop(ProgramContext&) override {}
    const char* status(const ProgramContext&) const override;

    bool awaiting_user() const override;
    void user_next() override { advance_requested_ = true; }

    std::size_t step_index() const { return step_index_; }

private:
    enum class Phase { Setup, Run, Teardown };

    bool run_setup(const RecipeStep& step, ProgramContext& ctx);
    bool step_done(const RecipeStep& step, const ProgramContext& ctx) const;
    bool run_teardown(const RecipeStep& step, ProgramContext& ctx);
    void advance();

    const Recipe* recipe_;
    std::size_t step_index_ = 0;
    Phase phase_ = Phase::Setup;
    std::uint8_t command_index_ = 0;
    Millis step_started_ms_ = 0;
    bool advance_requested_ = false;
};

} // namespace culina::app
