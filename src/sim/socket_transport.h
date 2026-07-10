#pragma once

#include "hal/i_uart.h"

namespace culina::sim {

// IUart over a Unix domain socket, for running the two processors as two
// real processes. Non-blocking on both ends; disconnects read as silence,
// exactly like an unplugged serial cable.
class SocketTransport : public hal::IUart {
public:
    // The MCU side listens, the app side connects.
    static SocketTransport listen_on(const char* path);
    static SocketTransport connect_to(const char* path);

    SocketTransport(SocketTransport&& other) noexcept;
    ~SocketTransport() override;

    SocketTransport(const SocketTransport&) = delete;
    SocketTransport& operator=(const SocketTransport&) = delete;
    SocketTransport& operator=(SocketTransport&&) = delete;

    bool connected();

    std::size_t write(const std::uint8_t* data, std::size_t len) override;
    bool read(std::uint8_t* out) override;

private:
    SocketTransport(int listen_fd, int conn_fd) : listen_fd_(listen_fd), conn_fd_(conn_fd) {}

    void accept_pending();

    int listen_fd_ = -1;
    int conn_fd_ = -1;
};

} // namespace culina::sim
