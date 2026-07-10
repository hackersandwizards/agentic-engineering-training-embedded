#pragma once

#include "common/units.h"
#include "protocol/c1link.h"

namespace culina::mcu {

// Safety rules evaluated by the MCU. See docs/safety-requirements.md.
class Interlocks {
public:
    struct Inputs {
        float temp_c = 20.0f;
        Rpm rpm = 0;
        bool lid_closed = true;
        bool lid_locked = false;
        bool motor_stalled = false;
    };

    // Clamps a requested motor speed against lid state and bowl temperature.
    Rpm clamp_speed_request(Rpm requested, const Inputs& in) const;

    // Continuous cap re-checked every tick; covers the lid, which can change
    // state at any moment while the motor runs.
    Rpm continuous_cap(const Inputs& in) const;

    // Hard trips.
    c1link::FaultCode evaluate(const Inputs& in) const;
};

} // namespace culina::mcu
