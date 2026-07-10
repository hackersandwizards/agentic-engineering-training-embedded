#pragma once

#include "app/telemetry_store.h"
#include "hal/i_clock.h"
#include "hal/i_uart.h"
#include "protocol/link.h"

namespace culina::app {

// Application-side view of the safety MCU: sends commands over C1-Link,
// routes telemetry into the store, and tracks the response to the most
// recent request.
class McuClient {
public:
    McuClient(hal::IUart* uart, const hal::IClock* clock, TelemetryStore* store)
        : link_(uart, clock), clock_(clock), store_(store) {}

    // Pump the link; call this every millisecond.
    void poll();

    Status request(c1link::MsgId id, const std::uint8_t* payload, std::uint16_t len);
    bool awaiting_response() const { return waiting_; }
    bool take_response(c1link::Frame* out);
    Status last_command_status() const { return last_command_status_; }
    void clear_command_status() { last_command_status_ = Status::Ok; }

    Status set_motor(Rpm rpm, std::uint8_t ramp_profile);
    Status motor_stop();
    Status set_heater(DeciCelsius target);
    Status heater_off();
    Status tare();
    Status lock_lid(bool locked);

    c1link::FaultCode last_fault() const { return last_fault_; }
    void clear_fault() { last_fault_ = c1link::FaultCode::None; }

    static constexpr Millis kResponseTimeoutMs = 50;
    static constexpr Millis kRequestDeadlineMs = 150;

private:
    c1link::Link link_;
    const hal::IClock* clock_;
    TelemetryStore* store_;
    std::uint8_t next_seq_ = 0;
    std::uint8_t pending_seq_ = 0;
    bool waiting_ = false;
    c1link::MsgId pending_msg_id_ = c1link::MsgId::Ping;
    bool response_ready_ = false;
    c1link::Frame response_;
    c1link::FaultCode last_fault_ = c1link::FaultCode::None;
    Millis sent_at_ms_ = 0;
    Millis request_started_ms_ = 0;
    bool retried_ = false;
    std::uint8_t pending_payload_[c1link::kMaxPayload] = {};
    std::uint16_t pending_payload_len_ = 0;
    Status last_command_status_ = Status::Ok;
    Millis last_tx_ms_ = 0;

    static constexpr Millis kHeartbeatIntervalMs = 1000;
};

} // namespace culina::app
