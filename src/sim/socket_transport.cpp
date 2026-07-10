#include "sim/socket_transport.h"

#include "common/logging.h"

#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <unistd.h>

namespace culina::sim {

namespace {

bool set_nonblocking(int fd) {
    const int flags = ::fcntl(fd, F_GETFL, 0);
    return flags >= 0 && ::fcntl(fd, F_SETFL, flags | O_NONBLOCK) == 0;
}

void prevent_sigpipe(int fd) {
#ifdef SO_NOSIGPIPE
    const int enabled = 1;
    ::setsockopt(fd, SOL_SOCKET, SO_NOSIGPIPE, &enabled, sizeof(enabled));
#else
    static_cast<void>(fd);
#endif
}

sockaddr_un make_address(const char* path) {
    sockaddr_un addr{};
    addr.sun_family = AF_UNIX;
    std::strncpy(addr.sun_path, path, sizeof(addr.sun_path) - 1);
    return addr;
}

} // namespace

SocketTransport SocketTransport::listen_on(const char* path) {
    if (path == nullptr || std::strlen(path) >= sizeof(sockaddr_un{}.sun_path)) {
        CULINA_LOG_ERROR("invalid socket path");
        return {-1, -1};
    }
    const int fd = ::socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0) {
        CULINA_LOG_ERROR("cannot create socket: %s", std::strerror(errno));
        return {-1, -1};
    }
    struct stat existing{};
    if (::lstat(path, &existing) == 0) {
        if (!S_ISSOCK(existing.st_mode) || existing.st_uid != ::geteuid() || ::unlink(path) != 0) {
            CULINA_LOG_ERROR("refusing to replace socket path %s", path);
            ::close(fd);
            return {-1, -1};
        }
    } else if (errno != ENOENT) {
        CULINA_LOG_ERROR("cannot inspect socket path %s: %s", path, std::strerror(errno));
        ::close(fd);
        return {-1, -1};
    }
    sockaddr_un addr = make_address(path);
    if (::bind(fd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) != 0 || ::listen(fd, 1) != 0) {
        CULINA_LOG_ERROR("cannot listen on %s: %s", path, std::strerror(errno));
        ::close(fd);
        return {-1, -1};
    }
    if (!set_nonblocking(fd)) {
        CULINA_LOG_ERROR("cannot configure socket: %s", std::strerror(errno));
        ::close(fd);
        return {-1, -1};
    }
    prevent_sigpipe(fd);
    return {fd, -1};
}

SocketTransport SocketTransport::connect_to(const char* path) {
    if (path == nullptr || std::strlen(path) >= sizeof(sockaddr_un{}.sun_path)) {
        CULINA_LOG_ERROR("invalid socket path");
        return {-1, -1};
    }
    const int fd = ::socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0) {
        CULINA_LOG_ERROR("cannot create socket: %s", std::strerror(errno));
        return {-1, -1};
    }
    sockaddr_un addr = make_address(path);
    if (::connect(fd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) != 0) {
        CULINA_LOG_ERROR("cannot connect to %s: %s", path, std::strerror(errno));
        ::close(fd);
        return {-1, -1};
    }
    if (!set_nonblocking(fd)) {
        CULINA_LOG_ERROR("cannot configure socket: %s", std::strerror(errno));
        ::close(fd);
        return {-1, -1};
    }
    prevent_sigpipe(fd);
    return {-1, fd};
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
        if (!set_nonblocking(fd)) {
            CULINA_LOG_WARN("cannot configure accepted socket: %s", std::strerror(errno));
            ::close(fd);
            return;
        }
        prevent_sigpipe(fd);
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
    int flags = 0;
#ifdef MSG_NOSIGNAL
    flags = MSG_NOSIGNAL;
#endif
    const ssize_t written = ::send(conn_fd_, data, len, flags);
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
        // Treat disconnects as a silent serial line.
        ::close(conn_fd_);
        conn_fd_ = -1;
    }
    return false;
}

} // namespace culina::sim
