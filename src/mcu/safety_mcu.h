#pragma once

#include "hal/i_clock.h"
#include "hal/i_heater.h"
#include "hal/i_lid.h"
#include "hal/i_motor.h"
#include "hal/i_scale.h"
#include "hal/i_temp_sensor.h"
#include "hal/i_uart.h"
#include "mcu/command_handler.h"
#include "mcu/heater_pid.h"
#include "mcu/interlocks.h"
#include "mcu/motor_controller.h"
#include "mcu/telemetry_publisher.h"
#include "protocol/link.h"

namespace culina::mcu {

// The safety/motor MCU firmware. Runs a 1 ms control tick: service the link,
// evaluate interlocks, drive heater and motor, publish telemetry.
class SafetyMcu {
public:
    struct Hardware {
        hal::IMotor* motor = nullptr;
        hal::IHeater* heater = nullptr;
        hal::ITempSensor* temp_sensor = nullptr;
        hal::IScale* scale = nullptr;
        hal::ILid* lid = nullptr;
    };

    SafetyMcu(const Hardware& hw, hal::IUart* uart, const hal::IClock* clock);

    void tick_1ms();

    c1link::FaultCode fault() const { return fault_; }

private:
    void sample_inputs();
    void enter_fault(c1link::FaultCode code);

    Hardware hw_;
    c1link::Link link_;
    MotorController motor_ctrl_;
    HeaterPid pid_;
    Interlocks interlocks_;
    CommandHandler handler_;
    TelemetryPublisher telemetry_;

    Interlocks::Inputs inputs_;
    c1link::FaultCode fault_ = c1link::FaultCode::None;
    std::uint32_t tick_count_ = 0;
};

} // namespace culina::mcu
