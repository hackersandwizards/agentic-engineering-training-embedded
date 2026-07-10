#include "sim/socket_transport.h"

#include "common/logging.h"

#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

namespace culina::sim {

namespace {

void set_nonblocking(int fd) {
    const int flags = ::fcntl(fd, F_GETFL, 0);
    ::fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

sockaddr_un make_address(const char* path) {
    sockaddr_un addr{};
    addr.sun_family = AF_UNIX;
    std::strncpy(addr.sun_path, path, sizeof(addr.sun_path) - 1);
    return addr;
}

} // namespace

SocketTransport SocketTransport::listen_on(const char* path) {
    const int fd = ::socket(AF_UNIX, SOCK_STREAM, 0);
    ::unlink(path);
    sockaddr_un addr = make_address(path);
    if (::bind(fd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) != 0 ||
        ::listen(fd, 1) != 0) {
        CULINA_LOG_ERROR("cannot listen on %s: %s", path, std::strerror(errno));
    }
    set_nonblocking(fd);
    return SocketTransport(fd, -1);
}

SocketTransport SocketTransport::connect_to(const char* path) {
    const int fd = ::socket(AF_UNIX, SOCK_STREAM, 0);
    sockaddr_un addr = make_address(path);
    if (::connect(fd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) != 0) {
        CULINA_LOG_ERROR("cannot connect to %s: %s", path, std::strerror(errno));
        ::close(fd);
        return SocketTransport(-1, -1);
    }
    set_nonblocking(fd);
    return SocketTransport(-1, fd);
}

SocketTransport::SocketTransport(SocketTransport&& other) noexcept
    : listen_fd_(other.listen_fd_), conn_fd_(other.conn_fd_) {
    other.listen_fd_ = -1;
    other.conn_fd_ = -1;
}

SocketTransport::~SocketTransport() {
    if (conn_fd_ >= 0) {
        ::close(conn_fd_);
    }
    if (listen_fd_ >= 0) {
        ::close(listen_fd_);
    }
}

void SocketTransport::accept_pending() {
    if (listen_fd_ < 0 || conn_fd_ >= 0) {
        return;
    }
    const int fd = ::accept(listen_fd_, nullptr, nullptr);
    if (fd >= 0) {
        set_nonblocking(fd);
        conn_fd_ = fd;
        CULINA_LOG_INFO("link partner connected");
    }
}

bool SocketTransport::connected() {
    accept_pending();
    return conn_fd_ >= 0;
}

std::size_t SocketTransport::write(const std::uint8_t* data, std::size_t len) {
    accept_pending();
    if (conn_fd_ < 0) {
        return 0;
    }
    const ssize_t written = ::send(conn_fd_, data, len, 0);
    if (written < 0) {
        if (errno != EAGAIN && errno != EWOULDBLOCK && errno != EPIPE) {
            CULINA_LOG_WARN("link write failed: %s", std::strerror(errno));
        }
        return 0;
    }
    return static_cast<std::size_t>(written);
}

bool SocketTransport::read(std::uint8_t* out) {
    accept_pending();
    if (conn_fd_ < 0) {
        return false;
    }
    const ssize_t got = ::recv(conn_fd_, out, 1, 0);
    if (got == 1) {
        return true;
    }
    if (got == 0) {
        // Peer went away; from the firmware's view the line just went quiet.
        ::close(conn_fd_);
        conn_fd_ = -1;
    }
    return false;
}

} // namespace culina::sim
