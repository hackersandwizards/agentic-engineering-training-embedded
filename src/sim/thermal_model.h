#pragma once

namespace culina::sim {

// First-order thermal plant for the bowl: heater power in, convective loss
// out, heat capacity grows with the mass in the bowl.
class ThermalModel {
public:
    void step(float dt_seconds, float heater_watts, float contents_grams);

    float temperature_c() const { return temperature_c_; }
    void set_ambient_c(float celsius);
    float ambient_c() const { return ambient_c_; }

private:
    float temperature_c_ = 20.0f;
    float ambient_c_ = 20.0f;
};

} // namespace culina::sim
