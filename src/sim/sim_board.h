#pragma once

#include "hal/i_heater.h"
#include "hal/i_lid.h"
#include "hal/i_motor.h"
#include "hal/i_scale.h"
#include "hal/i_temp_sensor.h"
#include "hal/i_watchdog.h"
#include "sim/lid_model.h"
#include "sim/motor_model.h"
#include "sim/scale_model.h"
#include "sim/sim_clock.h"
#include "sim/thermal_model.h"

#include <random>

namespace culina::sim {

// Wires the physical models to the HAL interfaces the firmware consumes and
// advances the whole world in lockstep with the simulated clock.
class SimBoard {
public:
    explicit SimBoard(std::uint32_t seed = 42);

    SimClock& clock() { return clock_; }
    const SimClock& clock() const { return clock_; }
    hal::IMotor& motor() { return motor_hal_; }
    hal::IHeater& heater() { return heater_hal_; }
    hal::ITempSensor& temp_sensor() { return temp_hal_; }
    hal::IScale& scale() { return scale_hal_; }
    hal::ILid& lid() { return lid_hal_; }
    hal::IWatchdog& app_watchdog() { return watchdog_; }

    // World and user actions, driven by scenarios and the CLI.
    void add_mass(float grams) { scale_model_.add_mass(grams); }
    void clear_mass() { scale_model_.clear_mass(); }
    void set_viscosity(float factor) { motor_model_.set_viscosity(factor); }
    void open_lid() { lid_model_.user_open(); }
    void close_lid() { lid_model_.user_close(); }
    void set_ambient_c(float celsius) { thermal_model_.set_ambient_c(celsius); }
    void set_temperature_c(float celsius) { thermal_model_.set_temperature_c(celsius); }
    void set_temp_sensor_failed(bool failed) { temp_hal_.set_failed(failed); }

    // Advance the world; granularity is 1 ms.
    void step_ms(std::uint32_t ms);

    // Ground truth for tests and the CLI status line.
    float true_temperature_c() const { return thermal_model_.temperature_c(); }
    float true_mass_g() const { return scale_model_.true_mass_g(); }
    bool lid_closed() const { return lid_model_.is_closed(); }
    bool watchdog_tripped() const { return watchdog_.tripped(); }

private:
    class MotorHal : public hal::IMotor {
    public:
        explicit MotorHal(MotorModel* model) : model_(model) {}
        void set_duty(float duty) override { model_->set_duty(duty); }
        void set_reverse(bool reverse) override { model_->set_reverse(reverse); }
        Rpm rpm() const override { return model_->rpm(); }
        std::uint16_t current_ma() const override { return model_->current_ma(); }
        bool stalled() const override { return model_->stalled(); }

    private:
        MotorModel* model_;
    };

    class HeaterHal : public hal::IHeater {
    public:
        void set_power_w(float watts) override {
            if (watts < 0.0f) {
                watts = 0.0f;
            }
            if (watts > kMaxWatts) {
                watts = kMaxWatts;
            }
            watts_ = watts;
        }
        float power_w() const override { return watts_; }

        static constexpr float kMaxWatts = 1200.0f;

    private:
        float watts_ = 0.0f;
    };

    class TempSensorHal : public hal::ITempSensor {
    public:
        TempSensorHal(const ThermalModel* model, std::uint32_t seed) : model_(model), rng_(seed) {}

        Result<DeciCelsius> read_deci_celsius() override {
            if (failed_) {
                return Result<DeciCelsius>::err(Status::HardwareFault);
            }
            const float reading = model_->temperature_c() + noise_(rng_);
            return Result<DeciCelsius>::ok(from_celsius(reading));
        }
        void set_failed(bool failed) { failed_ = failed; }

    private:
        const ThermalModel* model_;
        std::mt19937 rng_;
        std::normal_distribution<float> noise_{0.0f, 0.15f};
        bool failed_ = false;
    };

    class ScaleHal : public hal::IScale {
    public:
        explicit ScaleHal(ScaleModel* model) : model_(model) {}
        Result<std::int32_t> read_raw() override {
            return Result<std::int32_t>::ok(model_->read_raw_counts());
        }

    private:
        ScaleModel* model_;
    };

    class LidHal : public hal::ILid {
    public:
        explicit LidHal(LidModel* model) : model_(model) {}
        bool is_closed() const override { return model_->is_closed(); }
        bool is_locked() const override { return model_->is_locked(); }
        void set_lock(bool locked) override { model_->set_lock(locked); }

    private:
        LidModel* model_;
    };

    class Watchdog : public hal::IWatchdog {
    public:
        explicit Watchdog(const SimClock* clock) : clock_(clock) {}

        void feed() override {
            armed_ = true;
            last_feed_ms_ = clock_->now_ms();
        }
        Millis timeout_ms() const override { return kTimeoutMs; }

        void check() {
            if (armed_ && clock_->now_ms() - last_feed_ms_ > kTimeoutMs) {
                tripped_ = true;
            }
        }
        bool tripped() const { return tripped_; }

        static constexpr Millis kTimeoutMs = 500;

    private:
        const SimClock* clock_;
        Millis last_feed_ms_ = 0;
        bool armed_ = false;
        bool tripped_ = false;
    };

    SimClock clock_;
    ThermalModel thermal_model_;
    MotorModel motor_model_;
    ScaleModel scale_model_;
    LidModel lid_model_;

    MotorHal motor_hal_{&motor_model_};
    HeaterHal heater_hal_;
    TempSensorHal temp_hal_;
    ScaleHal scale_hal_{&scale_model_};
    LidHal lid_hal_{&lid_model_};
    Watchdog watchdog_{&clock_};
};

} // namespace culina::sim
