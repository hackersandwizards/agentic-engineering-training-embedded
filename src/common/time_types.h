#pragma once

#include <cstdint>

namespace culina {

// Measures monotonic microseconds since boot.
using Micros = std::uint64_t;

// Measures monotonic milliseconds since boot and wraps after about 49.7 days.
using Millis = std::uint32_t;

constexpr Millis to_millis(Micros us) {
    return static_cast<Millis>(us / 1000u);
}
constexpr Micros ms_to_us(std::uint32_t ms) {
    return static_cast<Micros>(ms) * 1000u;
}
constexpr Micros s_to_us(std::uint32_t s) {
    return static_cast<Micros>(s) * 1000000u;
}

} // namespace culina
