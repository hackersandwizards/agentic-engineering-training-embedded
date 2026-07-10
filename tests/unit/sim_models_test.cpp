#include "sim/motor_model.h"
#include "sim/scale_model.h"
#include "sim/thermal_model.h"

#include <gtest/gtest.h>

namespace {

using namespace culina::sim;

TEST(ThermalModel, HeatsHalfALitreOfWaterToBoilWithinTenMinutes) {
    ThermalModel model;
    float seconds = 0.0f;
    while (model.temperature_c() < 100.0f && seconds < 600.0f) {
        model.step(0.001f, 1000.0f, 500.0f);
        seconds += 0.001f;
    }
    EXPECT_GE(model.temperature_c(), 100.0f);
    EXPECT_GT(seconds, 120.0f); // not implausibly fast either
}

TEST(ThermalModel, CoolsTowardAmbientWithHeaterOff) {
    ThermalModel model;
    for (int i = 0; i < 300000; ++i) {
        model.step(0.001f, 800.0f, 500.0f);
    }
    const float hot = model.temperature_c();
    for (int i = 0; i < 600000; ++i) {
        model.step(0.001f, 0.0f, 500.0f);
    }
    EXPECT_LT(model.temperature_c(), hot);
    EXPECT_GT(model.temperature_c(), model.ambient_c() - 1.0f);
}

TEST(MotorModel, ReachesCommandedSpeed) {
    MotorModel motor;
    motor.set_duty(0.5f);
    for (int i = 0; i < 3000; ++i) {
        motor.step(0.001f, 500.0f);
    }
    EXPECT_NEAR(static_cast<float>(motor.rpm()), 5350.0f, 300.0f);
    EXPECT_FALSE(motor.stalled());
}

TEST(MotorModel, StallsOnThickDoughAtHighSpeed) {
    MotorModel motor;
    motor.set_viscosity(8.0f);
    motor.set_duty(1.0f);
    for (int i = 0; i < 5000; ++i) {
        motor.step(0.001f, 800.0f);
    }
    EXPECT_TRUE(motor.stalled());
    EXPECT_EQ(motor.rpm(), 0u);
    EXPECT_GT(motor.current_ma(), 2000u);
}

TEST(MotorModel, StallClearsWhenDriveDrops) {
    MotorModel motor;
    motor.set_viscosity(8.0f);
    motor.set_duty(1.0f);
    for (int i = 0; i < 5000; ++i) {
        motor.step(0.001f, 800.0f);
    }
    ASSERT_TRUE(motor.stalled());
    motor.set_duty(0.0f);
    motor.step(0.001f, 800.0f);
    EXPECT_FALSE(motor.stalled());
}

TEST(ScaleModel, ReadsTrueMassAtRest) {
    ScaleModel scale(7);
    scale.add_mass(500.0f);
    scale.step(0.001f, 0.0f);
    for (int i = 0; i < 20; ++i) {
        const float grams =
            static_cast<float>(scale.read_raw_counts()) / ScaleModel::kCountsPerGram;
        EXPECT_NEAR(grams, 500.0f, 3.0f);
    }
}

TEST(ScaleModel, VibratesAtHighMotorSpeed) {
    ScaleModel scale(7);
    scale.add_mass(500.0f);
    scale.step(0.001f, 10700.0f);
    float min_g = 1e9f;
    float max_g = -1e9f;
    for (int i = 0; i < 50; ++i) {
        const float grams =
            static_cast<float>(scale.read_raw_counts()) / ScaleModel::kCountsPerGram;
        min_g = grams < min_g ? grams : min_g;
        max_g = grams > max_g ? grams : max_g;
    }
    EXPECT_GT(max_g - min_g, 10.0f);
}

TEST(ScaleModel, SameSeedSameReadings) {
    ScaleModel a(11);
    ScaleModel b(11);
    a.add_mass(250.0f);
    b.add_mass(250.0f);
    for (int i = 0; i < 100; ++i) {
        a.step(0.001f, 3000.0f);
        b.step(0.001f, 3000.0f);
        EXPECT_EQ(a.read_raw_counts(), b.read_raw_counts());
    }
}

} // namespace
