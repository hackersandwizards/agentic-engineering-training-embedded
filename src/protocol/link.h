#pragma once

#include "hal/i_clock.h"
#include "hal/i_uart.h"
#include "common/result.h"
#include "protocol/frame_parser.h"

namespace culina::c1link {

// Framed transport over a UART: serializes outgoing frames and reassembles
// incoming ones, dropping partial frames that stall on the wire.
class Link {
public:
    Link(hal::IUart* uart, const hal::IClock* clock) : uart_(uart), clock_(clock) {}

    Status send(FrameType type, std::uint8_t seq, MsgId msg_id, const std::uint8_t* payload,
                std::uint16_t payload_len);

    // Pumps the UART. Returns true when a complete valid frame was received.
    bool poll(Frame* out);

    static constexpr Millis kFrameTimeoutMs = 50;

private:
    hal::IUart* uart_;
    const hal::IClock* clock_;
    FrameParser parser_;
    Millis frame_deadline_ms_ = 0;
};

} // namespace culina::c1link
