#pragma once

#include "common/result.h"
#include "hal/i_clock.h"
#include "hal/i_uart.h"
#include "protocol/frame_parser.h"

namespace culina::c1link {

// Frames UART traffic and drops partial frames that exceed the wire timeout.
class Link {
public:
    Link(hal::IUart* uart, const hal::IClock* clock) : uart_(uart), clock_(clock) {}

    Status send(FrameType type, std::uint8_t seq, MsgId msg_id, const std::uint8_t* payload,
                std::uint16_t payload_len);
    void cancel_pending_tx();

    // Pumps the UART. Returns true when a complete valid frame was received.
    bool poll(Frame* out);

    bool receiving() const { return parser_.in_progress(); }

    static constexpr Millis kFrameTimeoutMs = 50;

private:
    void flush_tx();

    hal::IUart* uart_;
    const hal::IClock* clock_;
    FrameParser parser_;
    Millis frame_deadline_ms_ = 0;
    static constexpr std::size_t kTxCapacity = kMaxFrameSize * 4;
    std::uint8_t tx_buffer_[kTxCapacity] = {};
    std::size_t tx_size_ = 0;
    std::size_t tx_offset_ = 0;
};

} // namespace culina::c1link
