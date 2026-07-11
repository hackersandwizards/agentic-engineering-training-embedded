#include "system/system_sim.h"

namespace culina::system {

SystemSim::SystemSim(std::uint32_t seed)
    : board_(seed), mcu_(hardware(), &transport_.mcu_side(), &board_.clock()) {}

mcu::SafetyMcu::Hardware SystemSim::hardware() {
    mcu::SafetyMcu::Hardware hw;
    hw.motor = &board_.motor();
    hw.heater = &board_.heater();
    hw.temp_sensor = &board_.temp_sensor();
    hw.scale = &board_.scale();
    hw.lid = &board_.lid();
    return hw;
}

void SystemSim::step_ms(std::uint32_t ms) {
    for (std::uint32_t i = 0; i < ms; ++i) {
        board_.step_ms(1);
        mcu_.tick_1ms();
        app_.tick_1ms();
    }
}

} // namespace culina::system
