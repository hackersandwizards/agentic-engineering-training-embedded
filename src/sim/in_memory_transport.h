#pragma once

#include "common/ring_buffer.h"
#include "hal/i_uart.h"

namespace culina::sim {

// Two IUart endpoints joined back-to-back. Fully deterministic; used by all
// tests and by the single-process simulator.
class InMemoryTransport {
public:
    hal::IUart& app_side() { return app_end_; }
    hal::IUart& mcu_side() { return mcu_end_; }

private:
    using Queue = RingBuffer<4096>;

    class Endpoint : public hal::IUart {
    public:
        Endpoint(Queue* tx, Queue* rx) : tx_(tx), rx_(rx) {}

        std::size_t write(const std::uint8_t* data, std::size_t len) override {
            std::size_t written = 0;
            while (written < len && tx_->push(data[written])) {
                ++written;
            }
            return written;
        }

        bool read(std::uint8_t* out) override { return rx_->pop(out); }

    private:
        Queue* tx_;
        Queue* rx_;
    };

    Queue app_to_mcu_;
    Queue mcu_to_app_;
    Endpoint app_end_{&app_to_mcu_, &mcu_to_app_};
    Endpoint mcu_end_{&mcu_to_app_, &app_to_mcu_};
};

} // namespace culina::sim
