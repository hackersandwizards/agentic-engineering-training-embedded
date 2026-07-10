#pragma once

#include "common/time_types.h"

namespace culina::hal {

// Firmware uses this monotonic source so target and simulation share time semantics.
class IClock {
public:
    virtual ~IClock() = default;
    virtual Micros now_us() const = 0;
    Millis now_ms() const { return to_millis(now_us()); }
};

} // namespace culina::hal
