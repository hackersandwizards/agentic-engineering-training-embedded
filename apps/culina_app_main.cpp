// Application processor as its own process. Connects to a running
// culina_mcu over the socket; commands execute in real time.

#include "app/mcu_client.h"
#include "app/telemetry_store.h"
#include "common/parse_number.h"
#include "sim/sim_clock.h"
#include "sim/socket_transport.h"

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <poll.h>
#include <string>
#include <unistd.h>

namespace {

class SafeStop {
public:
    void begin(culina::Millis now) {
        phase_ = Phase::Heater;
        request_sent_ = false;
        started_ms_ = now;
    }

    bool active() const { return phase_ != Phase::Idle; }
    bool expired(culina::Millis now) const { return active() && now - started_ms_ >= kDeadlineMs; }

    bool service(culina::app::McuClient* client, const culina::c1link::Frame* response) {
        using culina::c1link::FrameType;
        using culina::c1link::MsgId;

        if (response != nullptr && response->type == FrameType::Response) {
            if (phase_ == Phase::Heater && response->msg_id == MsgId::HeaterOff) {
                phase_ = Phase::Motor;
                request_sent_ = false;
            } else if (phase_ == Phase::Motor && response->msg_id == MsgId::MotorStop) {
                phase_ = Phase::Idle;
                request_sent_ = false;
                return true;
            }
        }
        if (client->last_command_status() != culina::Status::Ok) {
            client->clear_command_status();
            request_sent_ = false;
        }
        if (!request_sent_ && !client->awaiting_response()) {
            const culina::Status status =
                phase_ == Phase::Heater ? client->heater_off() : client->motor_stop();
            request_sent_ = status == culina::Status::Ok;
        }
        return false;
    }

private:
    enum class Phase { Idle, Heater, Motor };

    Phase phase_ = Phase::Idle;
    bool request_sent_ = false;
    culina::Millis started_ms_ = 0;
    static constexpr culina::Millis kDeadlineMs = 1000;
};

void print_status(const culina::app::TelemetryStore& store) {
    const auto sample = store.latest();
    std::printf("%.1f C  %u rpm  %ld g  flags 0x%02x\n",
                static_cast<double>(culina::to_celsius(sample.deci_celsius)), sample.rpm,
                static_cast<long>(sample.grams), sample.flags);
}

void print_command_status(culina::Status status) {
    std::printf("-> %s\n", culina::status_name(status));
}

} // namespace

int main(int argc, char** argv) {
    std::setvbuf(stdout, nullptr, _IOLBF, 0);

    const char* socket_path = "/tmp/c1link.sock";
    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "--socket") == 0 && i + 1 < argc) {
            socket_path = argv[++i];
        } else {
            std::fprintf(stderr, "usage: %s [--socket path]\n", argv[0]);
            return 2;
        }
    }

    auto uart = culina::sim::SocketTransport::connect_to(socket_path);
    if (!uart.connected()) {
        std::fprintf(stderr, "no MCU at %s - start culina_mcu first\n", socket_path);
        return 1;
    }

    culina::sim::SimClock clock;
    culina::app::TelemetryStore store;
    culina::app::McuClient client(&uart, &clock, &store);
    SafeStop safe_stop;
    bool quit_after_stop = false;

    std::printf("culina-app: connected to %s\n", socket_path);
    std::printf("commands: status | set-temp <c> | set-speed <dial> | tare | stop | quit\n");

    while (true) {
        clock.advance_us(1000);
        client.poll();

        if (!uart.connected()) {
            std::fprintf(stderr, "MCU link disconnected\n");
            return 1;
        }

        culina::c1link::Frame response;
        const bool has_response = client.take_response(&response);
        if (safe_stop.active()) {
            if (safe_stop.service(&client, has_response ? &response : nullptr)) {
                std::printf("-> stop complete\n");
                if (quit_after_stop) {
                    break;
                }
            } else if (safe_stop.expired(clock.now_ms())) {
                std::fprintf(stderr, "safe stop timed out\n");
                return 1;
            }
        } else if (has_response && response.type == culina::c1link::FrameType::Response) {
            std::printf("-> complete\n");
        } else if (has_response && response.type == culina::c1link::FrameType::Nack) {
            std::printf("-> protocol-error\n");
            client.clear_command_status();
        } else if (client.last_command_status() != culina::Status::Ok) {
            print_command_status(client.last_command_status());
            client.clear_command_status();
        }

        if (quit_after_stop) {
            ::poll(nullptr, 0, 1);
            continue;
        }

        pollfd input{STDIN_FILENO, POLLIN, 0};
        const int ready = ::poll(&input, 1, 1);
        if (ready < 0) {
            if (errno == EINTR) {
                continue;
            }
            std::fprintf(stderr, "stdin poll failed: %s\n", std::strerror(errno));
            safe_stop.begin(clock.now_ms());
            quit_after_stop = true;
            continue;
        }
        if (ready == 0 || (input.revents & (POLLIN | POLLHUP)) == 0) {
            continue;
        }

        std::string line;
        if (!std::getline(std::cin, line) || line == "quit" || line == "exit") {
            safe_stop.begin(clock.now_ms());
            quit_after_stop = true;
            continue;
        }
        if (safe_stop.active()) {
            std::printf("-> stop in progress\n");
            continue;
        }
        if (line == "status") {
            print_status(store);
        } else if (line.rfind("set-temp ", 0) == 0) {
            float celsius = 0.0f;
            if (!culina::parse_float(line.c_str() + 9, 0.0f, 160.0f, &celsius) ||
                (celsius > 0.0f && celsius < 37.0f)) {
                std::printf("-> invalid-argument\n");
                continue;
            }
            print_command_status(celsius == 0.0f
                                     ? client.heater_off()
                                     : client.set_heater(culina::from_celsius(celsius)));
        } else if (line.rfind("set-speed ", 0) == 0) {
            std::uint32_t dial = 0;
            if (!culina::parse_u32(line.c_str() + 10, 10, &dial)) {
                std::printf("-> invalid-argument\n");
                continue;
            }
            print_command_status(client.set_motor(static_cast<culina::Rpm>(dial * 1070u),
                                                  culina::c1link::kRampNormal));
        } else if (line == "tare") {
            print_command_status(client.tare());
        } else if (line == "stop") {
            safe_stop.begin(clock.now_ms());
        } else if (!line.empty()) {
            std::printf("unknown command\n");
        }
    }
    return 0;
}
