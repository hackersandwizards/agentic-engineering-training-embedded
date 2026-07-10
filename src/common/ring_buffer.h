#pragma once

#include <cstddef>
#include <cstdint>

namespace culina {

// Fixed-capacity single-producer/single-consumer byte queue used on both
// processors for UART buffering. No dynamic allocation.
template <std::size_t Capacity>
class RingBuffer {
    static_assert(Capacity >= 2, "RingBuffer needs at least two slots");

public:
    bool push(std::uint8_t byte) {
        if (count_ == Capacity - 1) {
            return false;
        }
        buf_[head_] = byte;
        head_ = (head_ + 1) % Capacity;
        ++count_;
        return true;
    }

    bool pop(std::uint8_t* out) {
        if (count_ == 0) {
            return false;
        }
        *out = buf_[tail_];
        tail_ = (tail_ + 1) % Capacity;
        --count_;
        return true;
    }

    bool empty() const { return count_ == 0; }
    std::size_t size() const { return count_; }
    static constexpr std::size_t capacity() { return Capacity; }

private:
    std::uint8_t buf_[Capacity] = {};
    std::size_t head_ = 0;
    std::size_t tail_ = 0;
    std::size_t count_ = 0;
};

} // namespace culina
