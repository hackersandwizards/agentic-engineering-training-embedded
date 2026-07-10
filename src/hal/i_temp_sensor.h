#pragma once

#include "common/result.h"
#include "common/units.h"

namespace culina::hal {

// NTC temperature probe at the bowl base. See docs/datasheets/heater-ntc.md.
class ITempSensor {
public:
    virtual ~ITempSensor() = default;
    virtual Result<DeciCelsius> read_deci_celsius() = 0;
};

} // namespace culina::hal
