#include "protocol/frame_parser.h"

#include "common/crc16.h"

namespace culina::c1link {

void FrameParser::reset() {
    state_ = State::Sync0;
    expected_len_ = 0;
    received_ = 0;
    running_crc_ = 0xFFFF;
}

void FrameParser::resync(std::uint8_t byte) {
    reset();
    if (byte == kSync0) {
        state_ = State::Sync1;
    }
}

bool FrameParser::feed(std::uint8_t byte, Frame* out) {
    // Sync and CRC bytes are outside the CRC range.
    if (state_ != State::Sync0 && state_ != State::Sync1 && state_ != State::CrcLo &&
        state_ != State::CrcHi) {
        running_crc_ = crc16_ccitt(&byte, 1, running_crc_);
    }
    switch (state_) {
    case State::Sync0:
        if (byte == kSync0) {
            state_ = State::Sync1;
        }
        return false;
    case State::Sync1:
        state_ = byte == kSync1 ? State::Version : byte == kSync0 ? State::Sync1 : State::Sync0;
        return false;
    case State::Version:
        if ((byte & 0xF0u) != (kVersion & 0xF0u)) {
            resync(byte);
            return false;
        }
        state_ = State::Type;
        return false;
    case State::Type:
        if (byte < 0x01 || byte > 0x04) {
            resync(byte);
            return false;
        }
        frame_.type = static_cast<FrameType>(byte);
        state_ = State::Seq;
        return false;
    case State::Seq:
        frame_.seq = byte;
        state_ = State::MsgId;
        return false;
    case State::MsgId:
        frame_.msg_id = static_cast<MsgId>(byte);
        state_ = State::LenLo;
        return false;
    case State::LenLo:
        expected_len_ = byte;
        state_ = State::LenHi;
        return false;
    case State::LenHi:
        expected_len_ =
            static_cast<std::uint16_t>(expected_len_ | (static_cast<std::uint16_t>(byte) << 8));
        if (expected_len_ > kMaxPayload) {
            resync(byte);
            return false;
        }
        received_ = 0;
        state_ = expected_len_ == 0 ? State::CrcLo : State::Payload;
        return false;
    case State::Payload:
        if (received_ < kMaxPayload) {
            frame_.payload[received_] = byte;
        }
        ++received_;
        if (received_ == expected_len_) {
            state_ = State::CrcLo;
        }
        return false;
    case State::CrcLo:
        crc_lo_ = byte;
        state_ = State::CrcHi;
        return false;
    case State::CrcHi: {
        const std::uint16_t wire_crc =
            static_cast<std::uint16_t>(crc_lo_ | (static_cast<std::uint16_t>(byte) << 8));
        if (running_crc_ != wire_crc) {
            resync(byte);
            return false;
        }
        frame_.payload_len = expected_len_;
        if (out == nullptr) {
            reset();
            return false;
        }
        *out = frame_;
        reset();
        return true;
    }
    }
    return false;
}

} // namespace culina::c1link
