#include "mcu/motor_controller.h"

namespace culina::mcu {

namespace {
float ramp_rate_for(std::uint8_t profile) {
    switch (profile) {
    case MotorController::kRampGentle:
        return 500.0f;
    case MotorController::kRampNormal:
        return 1500.0f;
    case MotorController::kRampFast:
        return 4000.0f;
    default:
        return 1500.0f;
    }
}
} // namespace

void MotorController::set_target(Rpm rpm, std::uint8_t ramp_profile) {
    if (rpm > 10700) {
        rpm = 10700;
    }
    target_rpm_ = rpm;
    ramp_rpm_per_s_ = ramp_rate_for(ramp_profile);
}

void MotorController::burst(Rpm rpm) {
    if (rpm > 10700) {
        rpm = 10700;
    }
    target_rpm_ = rpm;
    commanded_rpm_ = static_cast<float>(rpm);
}

void MotorController::stop() {
    target_rpm_ = 0;
    commanded_rpm_ = 0.0f;
    motor_->set_duty(0.0f);
}

void MotorController::enforce_cap(Rpm cap) {
    if (target_rpm_ > cap) {
        target_rpm_ = cap;
    }
    if (commanded_rpm_ > static_cast<float>(cap)) {
        commanded_rpm_ = static_cast<float>(cap);
    }
}

void MotorController::tick_1ms() {
    const float target = static_cast<float>(target_rpm_);
    const float max_step = ramp_rpm_per_s_ * 0.001f;
    if (commanded_rpm_ < target) {
        commanded_rpm_ += max_step;
        if (commanded_rpm_ > target) {
            commanded_rpm_ = target;
        }
    } else if (commanded_rpm_ > target) {
        commanded_rpm_ -= max_step * 4.0f; // decelerate faster than we accelerate
        if (commanded_rpm_ < target) {
            commanded_rpm_ = target;
        }
    }
    motor_->set_duty(commanded_rpm_ / 10700.0f);
}

} // namespace culina::mcu
