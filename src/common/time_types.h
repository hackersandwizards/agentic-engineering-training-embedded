#pragma once

#include <cstdint>

namespace culina {

// Monotonic microseconds since boot.
using Micros = std::uint64_t;

// Monotonic milliseconds since boot. 32 bits, wraps after ~49.7 days.
using Millis = std::uint32_t;

constexpr Millis to_millis(Micros us) { return static_cast<Millis>(us / 1000u); }
constexpr Micros ms_to_us(std::uint32_t ms) { return static_cast<Micros>(ms) * 1000u; }
constexpr Micros s_to_us(std::uint32_t s) { return static_cast<Micros>(s) * 1000000u; }

} // namespace culina
