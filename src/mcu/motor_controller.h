#pragma once

#include "common/units.h"
#include "hal/i_motor.h"

namespace culina::mcu {

// Ramps normal targets while burst commands take effect immediately.
class MotorController {
public:
    explicit MotorController(hal::IMotor* motor) : motor_(motor) {}

    void set_target(Rpm rpm, std::uint8_t ramp_profile);
    void burst(Rpm rpm);
    void stop();
    void enforce_cap(Rpm cap);
    void tick_1ms();

    Rpm target_rpm() const { return target_rpm_; }
    bool active() const { return target_rpm_ > 0 || commanded_rpm_ > 0.0f; }

private:
    hal::IMotor* motor_;
    float commanded_rpm_ = 0.0f;
    Rpm target_rpm_ = 0;
    float ramp_rpm_per_s_ = 500.0f;
};

} // namespace culina::mcu
