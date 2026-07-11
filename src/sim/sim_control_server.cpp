#include "sim/sim_control_server.h"

#include "common/logging.h"
#include "sim/sim_board.h"

#include <cerrno>
#include <cmath>
#include <cstring>
#include <fcntl.h>
#include <sstream>
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

void send_response(int fd, const std::string& response) {
    int flags = 0;
#ifdef MSG_NOSIGNAL
    flags = MSG_NOSIGNAL;
#endif
    static_cast<void>(::send(fd, response.data(), response.size(), flags));
}

sockaddr_un make_address(const char* path) {
    sockaddr_un address{};
    address.sun_family = AF_UNIX;
    std::strncpy(address.sun_path, path, sizeof(address.sun_path) - 1);
    return address;
}

float viscosity_for(const std::string& ingredient) {
    if (ingredient == "water") {
        return 1.0f;
    }
    if (ingredient == "oil") {
        return 1.8f;
    }
    if (ingredient == "flour") {
        return 6.5f;
    }
    return 2.0f;
}

} // namespace

SimControlServer SimControlServer::listen_on(const char* path, SimBoard* board) {
    if (path == nullptr) {
        return {-1, board};
    }
    if (board == nullptr || std::strlen(path) >= sizeof(sockaddr_un{}.sun_path)) {
        CULINA_LOG_ERROR("invalid simulation control socket");
        return {-1, board};
    }
    const int fd = ::socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0) {
        CULINA_LOG_ERROR("cannot create simulation control socket: %s", std::strerror(errno));
        return {-1, board};
    }
    struct stat existing = {};
    if (::lstat(path, &existing) == 0) {
        if (!S_ISSOCK(existing.st_mode) || existing.st_uid != ::geteuid() || ::unlink(path) != 0) {
            CULINA_LOG_ERROR("refusing to replace simulation control socket %s", path);
            ::close(fd);
            return {-1, board};
        }
    } else if (errno != ENOENT) {
        CULINA_LOG_ERROR("cannot inspect simulation control socket %s: %s", path,
                         std::strerror(errno));
        ::close(fd);
        return {-1, board};
    }
    const sockaddr_un address = make_address(path);
    if (::bind(fd, reinterpret_cast<const sockaddr*>(&address), sizeof(address)) != 0 ||
        ::listen(fd, 1) != 0 || !set_nonblocking(fd)) {
        CULINA_LOG_ERROR("cannot listen on simulation control socket %s: %s", path,
                         std::strerror(errno));
        ::close(fd);
        return {-1, board};
    }
    prevent_sigpipe(fd);
    return {fd, board};
}

SimControlServer::SimControlServer(SimControlServer&& other) noexcept
    : listen_fd_(other.listen_fd_), conn_fd_(other.conn_fd_), board_(other.board_),
      input_(std::move(other.input_)) {
    other.listen_fd_ = -1;
    other.conn_fd_ = -1;
}

SimControlServer::~SimControlServer() {
    if (conn_fd_ >= 0) {
        ::close(conn_fd_);
    }
    if (listen_fd_ >= 0) {
        ::close(listen_fd_);
    }
}

void SimControlServer::accept_pending() {
    if (listen_fd_ < 0 || conn_fd_ >= 0) {
        return;
    }
    const int fd = ::accept(listen_fd_, nullptr, nullptr);
    if (fd >= 0) {
        if (!set_nonblocking(fd)) {
            ::close(fd);
            return;
        }
        conn_fd_ = fd;
        prevent_sigpipe(conn_fd_);
        input_.clear();
    }
}

std::string SimControlServer::execute(const std::string& line) {
    std::istringstream stream(line);
    std::string command;
    stream >> command;
    if (command == "add") {
        float grams = 0.0f;
        std::string ingredient;
        std::string extra;
        if (!(stream >> grams >> ingredient) || stream >> extra || !std::isfinite(grams) ||
            grams < 0.1f || grams > 2200.0f - board_->true_mass_g() ||
            (ingredient != "water" && ingredient != "oil" && ingredient != "flour" &&
             ingredient != "other")) {
            return "error invalid add command\n";
        }
        board_->add_mass(grams);
        board_->set_viscosity(viscosity_for(ingredient));
        return "ok\n";
    }
    if (command == "lid") {
        std::string action;
        std::string extra;
        if (!(stream >> action) || stream >> extra || (action != "open" && action != "close")) {
            return "error invalid lid command\n";
        }
        if (action == "open") {
            board_->open_lid();
        } else {
            board_->close_lid();
        }
        return "ok\n";
    }
    return "error unknown command\n";
}

void SimControlServer::process_lines() {
    std::size_t newline = input_.find('\n');
    while (newline != std::string::npos) {
        const std::string response = execute(input_.substr(0, newline));
        input_.erase(0, newline + 1);
        send_response(conn_fd_, response);
        newline = input_.find('\n');
    }
    if (input_.size() > 512) {
        send_response(conn_fd_, "error command too long\n");
        input_.clear();
    }
}

void SimControlServer::poll() {
    accept_pending();
    if (conn_fd_ < 0) {
        return;
    }
    char buffer[256];
    while (true) {
        const ssize_t count = ::recv(conn_fd_, buffer, sizeof(buffer), 0);
        if (count > 0) {
            input_.append(buffer, static_cast<std::size_t>(count));
            process_lines();
            continue;
        }
        if (count == 0) {
            ::close(conn_fd_);
            conn_fd_ = -1;
            input_.clear();
        }
        break;
    }
}

} // namespace culina::sim
