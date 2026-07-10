#include "protocol/link.h"

#include "common/crc16.h"

#include <cstring>

namespace culina::c1link {

Status Link::send(FrameType type, std::uint8_t seq, MsgId msg_id, const std::uint8_t* payload,
                  std::uint16_t payload_len) {
    if (payload_len > kMaxPayload) {
        return Status::InvalidArgument;
    }
    std::uint8_t buf[kMaxFrameSize];
    buf[0] = kSync0;
    buf[1] = kSync1;
    buf[2] = kVersion;
    buf[3] = static_cast<std::uint8_t>(type);
    buf[4] = seq;
    buf[5] = static_cast<std::uint8_t>(msg_id);
    put_u16(&buf[6], payload_len);
    if (payload_len > 0) {
        std::memcpy(&buf[kHeaderSize], payload, payload_len);
    }
    const std::uint16_t crc = crc16_ccitt(payload, payload_len);
    put_u16(&buf[kHeaderSize + payload_len], crc);
    const std::size_t total = kHeaderSize + payload_len + kCrcSize;
    return uart_->write(buf, total) == total ? Status::Ok : Status::Overflow;
}

bool Link::poll(Frame* out) {
    std::uint8_t byte = 0;
    while (uart_->read(&byte)) {
        const bool was_idle = !parser_.in_progress();
        if (parser_.feed(byte, out)) {
            return true;
        }
        if (was_idle && parser_.in_progress()) {
            frame_deadline_ms_ = clock_->now_ms() + kFrameTimeoutMs;
        }
    }
    if (parser_.in_progress() && clock_->now_ms() > frame_deadline_ms_) {
        parser_.reset();
    }
    return false;
}

} // namespace culina::c1link
