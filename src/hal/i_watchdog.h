#pragma once

#include "common/time_types.h"

namespace culina::hal {

// Hardware watchdog. Firmware must call feed() at least once per timeout
// period or the supervisor resets the processor.
class IWatchdog {
public:
    virtual ~IWatchdog() = default;
    virtual void feed() = 0;
    virtual Millis timeout_ms() const = 0;
};

} // namespace culina::hal
