#pragma once

#include "common/result.h"

#include <cstdint>

namespace culina::hal {

// Returns raw ADC counts; conversion and tare belong above the HAL.
class IScale {
public:
    virtual ~IScale() = default;
    virtual Result<std::int32_t> read_raw() = 0;
};

} // namespace culina::hal
