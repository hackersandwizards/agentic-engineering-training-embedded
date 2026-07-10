#pragma once

#include <cstdint>

namespace culina {

// Temperatures travel as tenths of a degree Celsius, weights as whole grams,
// motor speed as RPM. Matches the C1-Link wire encoding.
using DeciCelsius = std::int16_t;
using Rpm = std::uint16_t;
using Grams = std::int32_t;

constexpr float to_celsius(DeciCelsius deci) { return static_cast<float>(deci) / 10.0f; }
constexpr DeciCelsius from_celsius(float celsius) {
    return static_cast<DeciCelsius>(celsius * 10.0f);
}

} // namespace culina
