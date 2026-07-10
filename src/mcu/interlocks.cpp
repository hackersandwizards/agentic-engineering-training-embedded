#include "mcu/interlocks.h"

namespace culina::mcu {

Rpm Interlocks::clamp_speed_request(Rpm requested, const Inputs& in) const {
    Rpm allowed = requested;
    if (!in.lid_closed && allowed > 500) {
        allowed = 500;
    }
    if (in.lid_closed && !in.lid_locked && allowed > 6400) {
        allowed = 6400;
    }
    if (in.temp_c > 60.0f && allowed > 6400) {
        allowed = 6400;
    }
    return allowed;
}

Rpm Interlocks::continuous_cap(const Inputs& in) const {
    if (!in.lid_closed) {
        return 500;
    }
    if (!in.lid_locked) {
        return 6400;
    }
    return 10700;
}

c1link::FaultCode Interlocks::evaluate(const Inputs& in) const {
    if (in.temp_c >= 165.0f) {
        return c1link::FaultCode::Overtemp;
    }
    if (in.motor_stalled) {
        return c1link::FaultCode::MotorStall;
    }
    return c1link::FaultCode::None;
}

} // namespace culina::mcu
