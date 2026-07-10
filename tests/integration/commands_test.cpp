#include "cli/commands.h"

#include <gtest/gtest.h>

namespace {

TEST(Commands, RejectsOutOfRangeInput) {
    culina::system::SystemSim sim;
    culina::cli::CommandEnv env{&sim, 0, false, false};

    EXPECT_FALSE(culina::cli::execute_command(env, "add water -1"));
    EXPECT_FALSE(culina::cli::execute_command(env, "add water nan"));
    EXPECT_FALSE(culina::cli::execute_command(env, "set-speed 11"));
    EXPECT_FALSE(culina::cli::execute_command(env, "wait 999999999999m"));
    EXPECT_FALSE(culina::cli::execute_command(env, "ota-verify 0 corrupt"));
    EXPECT_EQ(sim.board().true_mass_g(), 0.0f);
}

TEST(Commands, RefusesOtaDuringAnActiveCookingSession) {
    culina::system::SystemSim sim;
    culina::cli::CommandEnv env{&sim, 0, false, false};
    ASSERT_EQ(sim.controller().start_manual(800, 2, 60), culina::Status::Ok);

    EXPECT_FALSE(culina::cli::execute_command(env, "ota-verify 512"));
    EXPECT_FALSE(sim.ota().busy());
}

} // namespace
