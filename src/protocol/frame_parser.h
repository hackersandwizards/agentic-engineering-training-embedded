#pragma once

#include "protocol/c1link.h"

namespace culina::c1link {

// Incremental byte-stream parser. Feed one byte at a time; returns true when a
// complete, CRC-valid frame has been assembled into *out.
class FrameParser {
public:
    bool feed(std::uint8_t byte, Frame* out);
    void reset();
    bool in_progress() const { return state_ != State::Sync0; }

private:
    enum class State : std::uint8_t {
        Sync0,
        Sync1,
        Version,
        Type,
        Seq,
        MsgId,
        LenLo,
        LenHi,
        Payload,
        CrcLo,
        CrcHi,
    };

    State state_ = State::Sync0;
    Frame frame_;
    std::uint16_t expected_len_ = 0;
    std::uint16_t received_ = 0;
    std::uint8_t crc_lo_ = 0;
};

} // namespace culina::c1link
