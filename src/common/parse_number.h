#pragma once

#include <cerrno>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <limits>

namespace culina {

inline bool parse_float(const char* text, float min, float max, float* out) {
    if (text == nullptr || out == nullptr) {
        return false;
    }
    errno = 0;
    char* end = nullptr;
    const float value = std::strtof(text, &end);
    if (errno != 0 || end == text || *end != '\0' || !std::isfinite(value) || value < min ||
        value > max) {
        return false;
    }
    *out = value;
    return true;
}

inline bool parse_u32(const char* text, std::uint32_t max, std::uint32_t* out) {
    if (text == nullptr || out == nullptr || *text == '\0' || *text == '-') {
        return false;
    }
    errno = 0;
    char* end = nullptr;
    const unsigned long value = std::strtoul(text, &end, 10);
    if (errno != 0 || end == text || *end != '\0' || value > static_cast<unsigned long>(max) ||
        value > static_cast<unsigned long>(std::numeric_limits<std::uint32_t>::max())) {
        return false;
    }
    *out = static_cast<std::uint32_t>(value);
    return true;
}

} // namespace culina
