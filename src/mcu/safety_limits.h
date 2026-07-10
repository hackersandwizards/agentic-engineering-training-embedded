#pragma once

#include "common/units.h"

// Single home for the numbers behind docs/safety-requirements.md. Change
// them here or not at all.
namespace culina::mcu::limits {

constexpr Rpm kMaxRpm = 10700;

// SR-001 lid guard
constexpr Rpm kLidOpenMaxRpm = 500;
constexpr Rpm kUnlockedMaxRpm = 6400;

// SR-002 spill guard
constexpr float kSpillGuardTempC = 60.0f;
constexpr Rpm kSpillGuardMaxRpm = 6400;

// SR-003 overtemperature cutoff, above the 160.0 C user maximum
constexpr float kOvertempCutoffC = 165.0f;
constexpr DeciCelsius kHeaterMinTargetDeci = 370;
constexpr DeciCelsius kHeaterMaxTargetDeci = 1600;

} // namespace culina::mcu::limits
