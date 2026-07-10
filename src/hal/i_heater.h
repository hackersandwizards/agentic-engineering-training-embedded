#pragma once

namespace culina::hal {

// Power is in watts and clamped by the hardware driver.
class IHeater {
public:
    virtual ~IHeater() = default;
    virtual void set_power_w(float watts) = 0;
    virtual float power_w() const = 0;
};

} // namespace culina::hal
