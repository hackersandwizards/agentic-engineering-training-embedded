#include "mcu/motor_controller.h"
#include "protocol/c1link.h"

#include <gtest/gtest.h>

namespace {

class Motor final : public culina::hal::IMotor {
public:
    void set_duty(float duty) override { duty_ = duty; }
    void set_reverse(bool) override {}
    culina::Rpm rpm() const override { return 0; }
    std::uint16_t current_ma() const override { return 0; }
    bool stalled() const override { return false; }

    float duty() const { return duty_; }

private:
    float duty_ = 0.0f;
};

TEST(MotorController, FastRampStaysInsideTheDatasheetEnvelope) {
    Motor motor;
    culina::mcu::MotorController controller(&motor);
    controller.set_target(10700, culina::c1link::kRampFast);

    for (int i = 0; i < 1000; ++i) {
        controller.tick_1ms();
    }

    EXPECT_LE(motor.duty() * 10700.0f, 2500.0f);
}

} // namespace
