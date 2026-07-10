#pragma once

#include "common/units.h"
#include "protocol/c1link.h"

namespace culina::mcu {

// Enforces docs/safety-requirements.md.
class Interlocks {
public:
    struct Inputs {
        float temp_c = 20.0f;
        Rpm rpm = 0;
        bool lid_closed = true;
        bool lid_locked = false;
        bool motor_stalled = false;
    };

    Rpm clamp_speed_request(Rpm requested, const Inputs& in) const;

    // Recheck every tick because lid state can change while the motor runs.
    Rpm continuous_cap(const Inputs& in) const;

    c1link::FaultCode evaluate(const Inputs& in) const;
};

} // namespace culina::mcu
