#pragma once

#include "common/time_types.h"
#include "common/units.h"

namespace culina::mcu::limits {

constexpr Rpm kMaxRpm = 10700;

// SR-001 defines these lid guards.
constexpr Rpm kLidOpenMaxRpm = 500;
constexpr Rpm kUnlockedMaxRpm = 6400;
constexpr Rpm kUnlockMaxRpm = 100;

// SR-002 defines the spill guard.
constexpr float kSpillGuardTempC = 60.0f;
constexpr Rpm kSpillGuardMaxRpm = 6400;
constexpr Rpm kTareMaxRpm = 50;

// SR-003 places the cutoff above the 160.0 C user maximum.
constexpr float kOvertempCutoffC = 165.0f;
constexpr DeciCelsius kHeaterMinTargetDeci = 370;
constexpr DeciCelsius kHeaterMaxTargetDeci = 1600;
constexpr Millis kLinkTimeoutMs = 5000;

} // namespace culina::mcu::limits
