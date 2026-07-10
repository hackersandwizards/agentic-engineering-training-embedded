#pragma once

namespace culina::hal {

// Resistive heating element under the bowl. Power is commanded in watts and
// clamped by the driver to the element's physical maximum.
class IHeater {
public:
    virtual ~IHeater() = default;
    virtual void set_power_w(float watts) = 0;
    virtual float power_w() const = 0;
};

} // namespace culina::hal
