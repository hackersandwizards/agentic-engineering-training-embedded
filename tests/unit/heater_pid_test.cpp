#include "mcu/heater_pid.h"

#include <gtest/gtest.h>

namespace {

using culina::from_celsius;
using culina::mcu::HeaterPid;

TEST(HeaterPid, DisabledMeansNoPower) {
    HeaterPid pid;
    EXPECT_EQ(pid.update(20.0f, 0.001f), 0.0f);
    pid.set_target(from_celsius(100.0f));
    pid.disable();
    EXPECT_EQ(pid.update(20.0f, 0.001f), 0.0f);
}

TEST(HeaterPid, FullPowerWhenFarBelowTarget) {
    HeaterPid pid;
    pid.set_target(from_celsius(100.0f));
    EXPECT_EQ(pid.update(20.0f, 0.001f), 1200.0f);
}

TEST(HeaterPid, NoPowerAboveTarget) {
    HeaterPid pid;
    pid.set_target(from_celsius(65.0f));
    EXPECT_EQ(pid.update(70.0f, 0.001f), 0.0f);
}

} // namespace
