#include "mcu/interlocks.h"

#include "mcu/safety_limits.h"

namespace culina::mcu {

Rpm Interlocks::clamp_speed_request(Rpm requested, const Inputs& in) const {
    Rpm allowed = requested;
    if (!in.lid_closed && allowed > limits::kLidOpenMaxRpm) {
        allowed = limits::kLidOpenMaxRpm;
    }
    if (in.lid_closed && !in.lid_locked && allowed > limits::kUnlockedMaxRpm) {
        allowed = limits::kUnlockedMaxRpm;
    }
    if (in.temp_c > limits::kSpillGuardTempC && allowed > limits::kSpillGuardMaxRpm) {
        allowed = limits::kSpillGuardMaxRpm;
    }
    return allowed;
}

Rpm Interlocks::continuous_cap(const Inputs& in) const {
    if (!in.lid_closed) {
        return limits::kLidOpenMaxRpm;
    }
    if (!in.lid_locked) {
        return limits::kUnlockedMaxRpm;
    }
    return limits::kMaxRpm;
}

c1link::FaultCode Interlocks::evaluate(const Inputs& in) const {
    if (in.temp_c >= limits::kOvertempCutoffC) {
        return c1link::FaultCode::Overtemp;
    }
    if (in.motor_stalled) {
        return c1link::FaultCode::MotorStall;
    }
    return c1link::FaultCode::None;
}

} // namespace culina::mcu
