#include "protocol/link.h"

#include "protocol/frame_writer.h"

#include <cstring>

namespace culina::c1link {

Status Link::send(FrameType type, std::uint8_t seq, MsgId msg_id, const std::uint8_t* payload,
                  std::uint16_t payload_len) {
    if (payload_len > kMaxPayload || (payload_len > 0 && payload == nullptr)) {
        return Status::InvalidArgument;
    }
    if (tx_offset_ > 0) {
        const std::size_t queued = tx_size_ - tx_offset_;
        std::memmove(tx_buffer_, tx_buffer_ + tx_offset_, queued);
        tx_size_ = queued;
        tx_offset_ = 0;
    }
    const std::size_t frame_size = kHeaderSize + payload_len + kCrcSize;
    if (frame_size > kTxCapacity - tx_size_) {
        return Status::NotReady;
    }
    const std::size_t written = write_frame(tx_buffer_ + tx_size_, kTxCapacity - tx_size_, type,
                                            seq, msg_id, payload, payload_len);
    if (written == 0) {
        return Status::InvalidArgument;
    }
    tx_size_ += written;
    flush_tx();
    return Status::Ok;
}

void Link::cancel_pending_tx() {
    tx_offset_ = 0;
    tx_size_ = 0;
}

void Link::flush_tx() {
    if (tx_offset_ >= tx_size_) {
        return;
    }
    const std::size_t remaining = tx_size_ - tx_offset_;
    const std::size_t written = uart_->write(tx_buffer_ + tx_offset_, remaining);
    tx_offset_ += written > remaining ? remaining : written;
    if (tx_offset_ == tx_size_) {
        tx_offset_ = 0;
        tx_size_ = 0;
    }
}

bool Link::poll(Frame* out) {
    flush_tx();
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
