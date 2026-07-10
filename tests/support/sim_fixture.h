#pragma once

#include "app/cooking/cooking_controller.h"
#include "app/mcu_client.h"
#include "app/telemetry_store.h"
#include "mcu/safety_mcu.h"
#include "protocol/link.h"
#include "sim/in_memory_transport.h"
#include "sim/sim_board.h"

#include <vector>

namespace culina::testing {

// One simulated device: board, safety MCU, and an app-side link, advancing in
// lockstep 1 ms at a time.
class McuFixture {
public:
    McuFixture() : mcu_(hardware(), &transport_.mcu_side(), &board_.clock()) {}

    sim::SimBoard& board() { return board_; }
    c1link::Link& app_link() { return app_link_; }

    void run_ms(std::uint32_t ms) {
        for (std::uint32_t i = 0; i < ms; ++i) {
            board_.step_ms(1);
            mcu_.tick_1ms();
            pump_app();
        }
    }

    void send_request(c1link::MsgId id, const std::uint8_t* payload, std::uint16_t len) {
        app_link_.send(c1link::FrameType::Request, next_seq_++, id, payload, len);
    }

    const std::vector<c1link::Frame>& responses() const { return responses_; }
    const c1link::TelemetryData& last_telemetry() const { return last_telemetry_; }
    std::size_t telemetry_count() const { return telemetry_count_; }
    c1link::FaultCode last_fault() const { return last_fault_; }
    c1link::FaultCode mcu_fault() const { return mcu_.fault(); }

private:
    mcu::SafetyMcu::Hardware hardware() {
        mcu::SafetyMcu::Hardware hw;
        hw.motor = &board_.motor();
        hw.heater = &board_.heater();
        hw.temp_sensor = &board_.temp_sensor();
        hw.scale = &board_.scale();
        hw.lid = &board_.lid();
        return hw;
    }

    void pump_app() {
        c1link::Frame frame;
        while (app_link_.poll(&frame)) {
            if (frame.msg_id == c1link::MsgId::Telemetry &&
                frame.payload_len == c1link::kTelemetryPayloadSize) {
                last_telemetry_.tick = c1link::get_u32(frame.payload);
                last_telemetry_.deci_celsius = c1link::get_i16(frame.payload + 4);
                last_telemetry_.rpm = c1link::get_u16(frame.payload + 6);
                last_telemetry_.grams = c1link::get_i32(frame.payload + 8);
                last_telemetry_.flags = frame.payload[12];
                ++telemetry_count_;
            } else if (frame.msg_id == c1link::MsgId::Fault && frame.payload_len == 1) {
                last_fault_ = static_cast<c1link::FaultCode>(frame.payload[0]);
            } else {
                responses_.push_back(frame);
            }
        }
    }

    sim::SimBoard board_;
    sim::InMemoryTransport transport_;
    mcu::SafetyMcu mcu_;
    c1link::Link app_link_{&transport_.app_side(), &board_.clock()};
    std::uint8_t next_seq_ = 0;
    std::vector<c1link::Frame> responses_;
    c1link::TelemetryData last_telemetry_;
    std::size_t telemetry_count_ = 0;
    c1link::FaultCode last_fault_ = c1link::FaultCode::None;
};

// The full device: board, safety MCU, and the application firmware stack.
class SystemFixture {
public:
    SystemFixture() : mcu_(hardware(), &transport_.mcu_side(), &board_.clock()) {}

    sim::SimBoard& board() { return board_; }
    app::TelemetryStore& store() { return store_; }
    app::McuClient& client() { return client_; }
    app::CookingController& controller() { return controller_; }

    void run_ms(std::uint32_t ms) {
        for (std::uint32_t i = 0; i < ms; ++i) {
            board_.step_ms(1);
            mcu_.tick_1ms();
            client_.poll();
            if (++app_divider_ >= 10) {
                app_divider_ = 0;
                controller_.tick_10ms();
            }
        }
    }

private:
    mcu::SafetyMcu::Hardware hardware() {
        mcu::SafetyMcu::Hardware hw;
        hw.motor = &board_.motor();
        hw.heater = &board_.heater();
        hw.temp_sensor = &board_.temp_sensor();
        hw.scale = &board_.scale();
        hw.lid = &board_.lid();
        return hw;
    }

    sim::SimBoard board_;
    sim::InMemoryTransport transport_;
    mcu::SafetyMcu mcu_;
    app::TelemetryStore store_;
    app::McuClient client_{&transport_.app_side(), &board_.clock(), &store_};
    app::CookingController controller_{&client_, &store_, &board_.clock(),
                                       &board_.app_watchdog()};
    std::uint32_t app_divider_ = 0;
};

} // namespace culina::testing
