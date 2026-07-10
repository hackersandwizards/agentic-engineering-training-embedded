#pragma once

#include "common/units.h"

#include <cstdint>

namespace culina::hal {

// Duty is normalized to [0.0, 1.0].
class IMotor {
public:
    virtual ~IMotor() = default;
    virtual void set_duty(float duty) = 0;
    virtual void set_reverse(bool reverse) = 0;
    virtual Rpm rpm() const = 0;
    virtual std::uint16_t current_ma() const = 0;
    virtual bool stalled() const = 0;
};

} // namespace culina::hal
