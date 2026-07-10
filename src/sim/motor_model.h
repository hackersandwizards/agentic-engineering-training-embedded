#pragma once

#include "common/units.h"

#include <cstdint>

namespace culina::sim {

// Motor with first-order speed response and a crude load model: torque demand
// grows with speed, viscosity, and bowl mass. Overload collapses the speed and
// raises the stall flag until the drive command drops to zero.
class MotorModel {
public:
    void step(float dt_seconds, float contents_grams);

    void set_duty(float duty);
    void set_reverse(bool reverse) { reverse_ = reverse; }
    void set_viscosity(float factor) { viscosity_ = factor; }

    Rpm rpm() const { return static_cast<Rpm>(rpm_ < 0.0f ? 0.0f : rpm_); }
    bool reverse() const { return reverse_; }
    std::uint16_t current_ma() const { return current_ma_; }
    bool stalled() const { return stalled_; }

private:
    float duty_ = 0.0f;
    float rpm_ = 0.0f;
    float viscosity_ = 1.0f;
    bool reverse_ = false;
    bool stalled_ = false;
    std::uint16_t current_ma_ = 0;
};

} // namespace culina::sim
