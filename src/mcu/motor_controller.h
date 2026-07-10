#pragma once

#include "common/units.h"
#include "hal/i_motor.h"

namespace culina::mcu {

// Ramped speed control on top of the raw motor driver. Profiles trade
// smoothness against responsiveness; burst() is the immediate path used for
// short pulse operations.
class MotorController {
public:
    explicit MotorController(hal::IMotor* motor) : motor_(motor) {}

    void set_target(Rpm rpm, std::uint8_t ramp_profile);
    void burst(Rpm rpm);
    void stop();
    void enforce_cap(Rpm cap);
    void tick_1ms();

    Rpm target_rpm() const { return target_rpm_; }

    static constexpr std::uint8_t kRampGentle = 0;
    static constexpr std::uint8_t kRampNormal = 1;
    static constexpr std::uint8_t kRampFast = 2;
    static constexpr std::uint8_t kRampBurst = 3;

private:
    hal::IMotor* motor_;
    float commanded_rpm_ = 0.0f;
    Rpm target_rpm_ = 0;
    float ramp_rpm_per_s_ = 500.0f;
};

} // namespace culina::mcu
