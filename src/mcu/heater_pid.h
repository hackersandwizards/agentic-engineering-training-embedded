#pragma once

#include "common/units.h"

namespace culina::mcu {

class HeaterPid {
public:
    void set_target(DeciCelsius target);
    void disable();
    bool enabled() const { return enabled_; }
    DeciCelsius target() const { return target_deci_; }

    // Returns the commanded heater power in watts.
    float update(float measured_c, float dt_seconds);

private:
    bool enabled_ = false;
    DeciCelsius target_deci_ = 0;
    float integral_ = 0.0f;
};

} // namespace culina::mcu
