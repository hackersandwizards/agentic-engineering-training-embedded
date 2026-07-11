#include "sim/sim_control_server.h"

#include "sim/sim_board.h"

#include <gtest/gtest.h>

#include <array>
#include <cstdio>
#include <string>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

namespace culina::sim {
namespace {

class SimControlServerTest : public ::testing::Test {
protected:
    void SetUp() override {
        path_ = "/tmp/culina-control-test-" + std::to_string(::getpid()) + ".sock";
        server_ =
            std::make_unique<SimControlServer>(SimControlServer::listen_on(path_.c_str(), &board_));
        ASSERT_TRUE(server_->valid());

        client_ = ::socket(AF_UNIX, SOCK_STREAM, 0);
        ASSERT_GE(client_, 0);
        sockaddr_un address{};
        address.sun_family = AF_UNIX;
        std::snprintf(address.sun_path, sizeof(address.sun_path), "%s", path_.c_str());
        ASSERT_EQ(::connect(client_, reinterpret_cast<sockaddr*>(&address), sizeof(address)), 0);
    }

    void TearDown() override {
        if (client_ >= 0) {
            ::close(client_);
        }
        server_.reset();
        ::unlink(path_.c_str());
    }

    std::string exchange(const std::string& command) {
        EXPECT_EQ(::write(client_, command.data(), command.size()),
                  static_cast<ssize_t>(command.size()));
        for (int i = 0; i < 20; ++i) {
            server_->poll();
        }
        std::array<char, 128> response{};
        const ssize_t count = ::read(client_, response.data(), response.size());
        EXPECT_GT(count, 0);
        return std::string(response.data(), static_cast<std::size_t>(count));
    }

    SimBoard board_;
    std::string path_;
    std::unique_ptr<SimControlServer> server_;
    int client_ = -1;
};

TEST_F(SimControlServerTest, AddsIngredient) {
    EXPECT_EQ(exchange("add 250 flour\n"), "ok\n");
    EXPECT_FLOAT_EQ(board_.true_mass_g(), 250.0f);
}

TEST_F(SimControlServerTest, OperatesThePhysicalLid) {
    EXPECT_EQ(exchange("lid open\n"), "ok\n");
    EXPECT_FALSE(board_.lid_closed());
    EXPECT_EQ(exchange("lid close\n"), "ok\n");
    EXPECT_TRUE(board_.lid_closed());
}

TEST_F(SimControlServerTest, RejectsMalformedAndOutOfRangeCommands) {
    EXPECT_EQ(exchange("add 0 water\n"), "error invalid add command\n");
    EXPECT_EQ(exchange("add 3000 water\n"), "error invalid add command\n");
    EXPECT_EQ(exchange("lid remove\n"), "error invalid lid command\n");
    EXPECT_EQ(exchange("unknown\n"), "error unknown command\n");
    EXPECT_FLOAT_EQ(board_.true_mass_g(), 0.0f);
}

TEST_F(SimControlServerTest, BuffersPartialCommands) {
    ASSERT_EQ(::write(client_, "add 1", 5), 5);
    server_->poll();
    ASSERT_EQ(::write(client_, "00 oil\n", 7), 7);
    for (int i = 0; i < 20; ++i) {
        server_->poll();
    }

    std::array<char, 16> response{};
    const ssize_t count = ::read(client_, response.data(), response.size());
    ASSERT_GT(count, 0);
    EXPECT_EQ(std::string(response.data(), static_cast<std::size_t>(count)), "ok\n");
    EXPECT_FLOAT_EQ(board_.true_mass_g(), 100.0f);
}

} // namespace
} // namespace culina::sim
