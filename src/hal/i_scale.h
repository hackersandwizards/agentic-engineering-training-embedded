#pragma once

#include "common/result.h"

#include <cstdint>

namespace culina::hal {

// Load cell under the bowl. Returns raw ADC counts; conversion to grams and
// tare handling live above the HAL.
class IScale {
public:
    virtual ~IScale() = default;
    virtual Result<std::int32_t> read_raw() = 0;
};

} // namespace culina::hal
