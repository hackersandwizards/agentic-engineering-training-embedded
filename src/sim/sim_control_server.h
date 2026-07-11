#pragma once

#include <string>

namespace culina::sim {

class SimBoard;

class SimControlServer {
public:
    static SimControlServer listen_on(const char* path, SimBoard* board);

    SimControlServer(SimControlServer&& other) noexcept;
    ~SimControlServer();

    SimControlServer(const SimControlServer&) = delete;
    SimControlServer& operator=(const SimControlServer&) = delete;
    SimControlServer& operator=(SimControlServer&&) = delete;

    bool valid() const { return listen_fd_ >= 0; }
    void poll();

private:
    SimControlServer(int listen_fd, SimBoard* board) : listen_fd_(listen_fd), board_(board) {}

    void accept_pending();
    void process_lines();
    std::string execute(const std::string& line);

    int listen_fd_ = -1;
    int conn_fd_ = -1;
    SimBoard* board_ = nullptr;
    std::string input_;
};

} // namespace culina::sim
