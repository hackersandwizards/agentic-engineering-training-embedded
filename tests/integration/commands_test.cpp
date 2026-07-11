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

TEST(Commands, ChecksTheActiveProgramByName) {
    culina::system::SystemSim sim;
    culina::cli::CommandEnv env{&sim, 0, false, false};

    EXPECT_TRUE(culina::cli::execute_command(env, "expect program == none"));
    EXPECT_EQ(env.expect_failures, 0);

    ASSERT_TRUE(culina::cli::execute_command(env, "manual 80 2 60"));
    ASSERT_TRUE(culina::cli::execute_command(env, "wait 100ms"));
    EXPECT_TRUE(culina::cli::execute_command(env, "expect program == manual"));
    EXPECT_EQ(env.expect_failures, 0);
}

} // namespace
