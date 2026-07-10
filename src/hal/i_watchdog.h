#pragma once

#include "common/time_types.h"

namespace culina::hal {

// feed() must run before timeout_ms() or hardware resets the processor.
class IWatchdog {
public:
    virtual ~IWatchdog() = default;
    virtual void feed() = 0;
    virtual Millis timeout_ms() const = 0;
};

} // namespace culina::hal
