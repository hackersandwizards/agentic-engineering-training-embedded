#include "app/cooking/guided_recipe.h"
#include "support/sim_fixture.h"

#include <cstring>
#include <gtest/gtest.h>

namespace {

using namespace culina;
using culina::app::Recipe;
using culina::app::SessionState;
using culina::app::StepKind;
using culina::testing::SystemFixture;

Recipe two_step_recipe() {
    Recipe recipe;
    std::strcpy(recipe.name, "Test Shake");
    recipe.steps[0].kind = StepKind::Mix;
    recipe.steps[0].dial_speed = 4;
    recipe.steps[0].duration_s = 5;
    std::strcpy(recipe.steps[0].text, "Blend it");
    recipe.steps[1].kind = StepKind::Note;
    std::strcpy(recipe.steps[1].text, "Pour and serve");
    recipe.step_count = 2;
    return recipe;
}

TEST(GuidedRecipe, RunsStepsAndWaitsForTheUser) {
    SystemFixture fix;
    fix.board().add_mass(400.0f);
    const Recipe recipe = two_step_recipe();
    ASSERT_EQ(fix.controller().start_recipe(&recipe), Status::Ok);

    fix.run_ms(3000); // mid mix step
    EXPECT_GT(fix.store().latest().rpm, 3500u);
    EXPECT_FALSE(fix.controller().awaiting_user());
    EXPECT_STREQ(fix.controller().program_status(), "Blend it");

    fix.run_ms(4000); // mix over, note step waits
    EXPECT_EQ(fix.store().latest().rpm, 0u);
    EXPECT_TRUE(fix.controller().awaiting_user());
    EXPECT_STREQ(fix.controller().program_status(), "Pour and serve");
    EXPECT_EQ(fix.controller().state(), SessionState::Running);

    fix.controller().user_next();
    fix.run_ms(200);
    EXPECT_EQ(fix.controller().state(), SessionState::Done);
}

TEST(GuidedRecipe, EmptyRecipeIsRefused) {
    SystemFixture fix;
    Recipe empty;
    EXPECT_EQ(fix.controller().start_recipe(&empty), Status::InvalidArgument);
}

} // namespace
