#include "protocol/link.h"

#include "protocol/frame_writer.h"

namespace culina::c1link {

Status Link::send(FrameType type, std::uint8_t seq, MsgId msg_id, const std::uint8_t* payload,
                  std::uint16_t payload_len) {
    std::uint8_t buf[kMaxFrameSize];
    const std::size_t total = write_frame(buf, sizeof(buf), type, seq, msg_id, payload,
                                          payload_len);
    if (total == 0) {
        return Status::InvalidArgument;
    }
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
    // Signed difference survives the 32-bit millisecond wraparound.
    if (parser_.in_progress() &&
        static_cast<std::int32_t>(clock_->now_ms() - frame_deadline_ms_) > 0) {
        parser_.reset();
    }
    return false;
}

} // namespace culina::c1link
