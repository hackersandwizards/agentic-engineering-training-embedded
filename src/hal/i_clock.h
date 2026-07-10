#pragma once

#include "common/time_types.h"

namespace culina::hal {

// Monotonic time source. All firmware code takes time from here — never from
// the host OS — so behaviour is identical on target and in simulation.
class IClock {
public:
    virtual ~IClock() = default;
    virtual Micros now_us() const = 0;
    Millis now_ms() const { return to_millis(now_us()); }
};

} // namespace culina::hal
