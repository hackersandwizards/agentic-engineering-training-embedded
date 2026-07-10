#pragma once

#include "hal/i_uart.h"

#include <cstring>
#include <vector>

namespace culina::testing {

// UART decorator for fault injection: swallow a write entirely, or hold one
// back and release it later.
class FlakyTransport : public hal::IUart {
public:
    explicit FlakyTransport(hal::IUart* inner) : inner_(inner) {}

    void drop_next_write() { drop_next_ = true; }
    void hold_next_write() { hold_next_ = true; }

    // Puts a held write back on the wire.
    void release_held() {
        if (!held_.empty()) {
            inner_->write(held_.data(), held_.size());
            held_.clear();
        }
    }

    std::size_t write(const std::uint8_t* data, std::size_t len) override {
        if (drop_next_) {
            drop_next_ = false;
            return len; // pretend it went out
        }
        if (hold_next_) {
            hold_next_ = false;
            held_.assign(data, data + len);
            return len;
        }
        return inner_->write(data, len);
    }

    bool read(std::uint8_t* out) override { return inner_->read(out); }

private:
    hal::IUart* inner_;
    bool drop_next_ = false;
    bool hold_next_ = false;
    std::vector<std::uint8_t> held_;
};

} // namespace culina::testing
