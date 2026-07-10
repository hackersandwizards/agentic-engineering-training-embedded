#include "app/cooking/dough_mode.h"
#include "app/cooking/sous_vide_mode.h"
#include "app/cooking/turbo_pulse.h"
#include "common/crc16.h"
#include "support/sim_fixture.h"

#include <gtest/gtest.h>

#include <vector>

namespace {

using namespace culina;
using culina::app::SessionState;
using culina::testing::SystemFixture;

TEST(Cooking, ManualModeBoilsWaterAndShutsDown) {
    SystemFixture fix;
    fix.board().add_mass(500.0f);
    ASSERT_EQ(fix.controller().start_manual(1000, 2, 330), Status::Ok);
    EXPECT_EQ(fix.controller().state(), SessionState::Running);

    fix.run_ms(320000);
    EXPECT_GE(fix.board().true_temperature_c(), 97.0f);
    EXPECT_GT(fix.store().latest().rpm, 1800u);

    fix.run_ms(20000); // past the programmed duration
    EXPECT_EQ(fix.controller().state(), SessionState::Done);
    EXPECT_EQ(fix.board().heater().power_w(), 0.0f);
    fix.run_ms(3000);
    EXPECT_EQ(fix.store().latest().rpm, 0u);
    EXPECT_FALSE(fix.board().watchdog_tripped());
}

TEST(Cooking, DoughModeAlternatesKneadAndRest) {
    SystemFixture fix;
    fix.board().add_mass(600.0f);
    ASSERT_EQ(fix.controller().start_program(std::make_unique<app::DoughMode>(60)), Status::Ok);

    fix.run_ms(3000); // mid knead phase
    EXPECT_GT(fix.store().latest().rpm, 2800u);

    fix.run_ms(2600); // 5.6 s: rest phase
    EXPECT_LT(fix.store().latest().rpm, 500u);

    fix.run_ms(2000); // 7.6 s: kneading again
    EXPECT_GT(fix.store().latest().rpm, 2800u);
}

TEST(Cooking, SousVideHoldsTheBathTemperature) {
    SystemFixture fix;
    fix.board().add_mass(1500.0f);
    auto mode = std::make_unique<app::SousVideMode>(650, 3600);
    const app::SousVideMode* sous_vide = mode.get();
    ASSERT_EQ(fix.controller().start_program(std::move(mode)), Status::Ok);

    fix.run_ms(900000); // 15 simulated minutes to stabilize
    EXPECT_NEAR(fix.controller().display_avg_temp_c(), 65.0f, 1.5f);
    EXPECT_EQ(fix.controller().state(), SessionState::Running);
    EXPECT_TRUE(fix.controller().hot_bowl());
    EXPECT_TRUE(sous_vide->at_temperature());
    EXPECT_STREQ(fix.controller().program_status(), "at temperature");
}

TEST(Cooking, TurboPulseLocksSpinsAndReleases) {
    SystemFixture fix;
    fix.board().add_mass(300.0f);
    ASSERT_EQ(fix.controller().start_program(std::make_unique<app::TurboPulse>(1500)),
              Status::Ok);

    fix.run_ms(1200);
    EXPECT_TRUE((fix.store().latest().flags & c1link::kFlagLidLocked) != 0);
    EXPECT_GT(fix.store().latest().rpm, 8000u);

    fix.run_ms(6000);
    EXPECT_EQ(fix.controller().state(), SessionState::Done);
    EXPECT_EQ(fix.store().latest().rpm, 0u);
    EXPECT_TRUE((fix.store().latest().flags & c1link::kFlagLidLocked) == 0);
}

TEST(Cooking, OtaVerificationKeepsTheWatchdogFed) {
    SystemFixture fix;
    fix.run_ms(100); // normal operation arms the watchdog

    static std::vector<std::uint8_t> image(512 * 1024);
    for (std::size_t i = 0; i < image.size(); ++i) {
        image[i] = static_cast<std::uint8_t>(i * 7 + 3);
    }
    const std::uint16_t crc = culina::crc16_ccitt(image.data(), image.size());

    app::OtaUpdater ota;
    fix.controller().attach_ota(&ota);
    ASSERT_EQ(ota.begin(image.data(), image.size(), crc), Status::Ok);

    // 128 chunks at one per 10 ms tick: well past the 500 ms watchdog
    // timeout if verification stops the feeding.
    fix.run_ms(3000);
    EXPECT_EQ(ota.state(), app::OtaUpdater::State::Ready);
    EXPECT_FALSE(fix.board().watchdog_tripped());
}

TEST(Cooking, FaultTakesTheSessionDown) {
    SystemFixture fix;
    fix.board().add_mass(200.0f);
    ASSERT_EQ(fix.controller().start_manual(1500, 0, 3600), Status::Ok);
    fix.board().set_ambient_c(175.0f);
    fix.run_ms(300000);
    EXPECT_EQ(fix.controller().state(), SessionState::Faulted);
    EXPECT_EQ(fix.board().heater().power_w(), 0.0f);
}

} // namespace
