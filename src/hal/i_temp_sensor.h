#pragma once

#include "common/result.h"
#include "common/units.h"

namespace culina::hal {

// Reads the bowl-base NTC described in docs/datasheets/heater-ntc.md.
class ITempSensor {
public:
    virtual ~ITempSensor() = default;
    virtual Result<DeciCelsius> read_deci_celsius() = 0;
};

} // namespace culina::hal
