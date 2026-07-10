// Application processor as its own process. Connects to a running
// culina_mcu over the socket; commands execute in real time.

#include "app/mcu_client.h"
#include "app/telemetry_store.h"
#include "sim/sim_clock.h"
#include "sim/socket_transport.h"

#include <atomic>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <thread>

namespace {

std::atomic<bool> g_quit{false};

void pump(culina::sim::SimClock* clock, culina::app::McuClient* client) {
    while (!g_quit.load()) {
        clock->advance_us(1000);
        client->poll();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

} // namespace

int main(int argc, char** argv) {
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
    std::thread pumper(pump, &clock, &client);

    std::printf("culina-app: connected to %s\n", socket_path);
    std::printf("commands: status | set-temp <c> | set-speed <dial> | tare | stop | quit\n");

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "quit" || line == "exit") {
            break;
        }
        if (line == "status") {
            const auto s = store.latest();
            std::printf("%.1f C  %u rpm  %ld g  flags 0x%02x\n",
                        static_cast<double>(culina::to_celsius(s.deci_celsius)), s.rpm,
                        static_cast<long>(s.grams), s.flags);
        } else if (line.rfind("set-temp ", 0) == 0) {
            const float c = std::strtof(line.c_str() + 9, nullptr);
            const auto status = c <= 0.0f ? client.heater_off()
                                          : client.set_heater(culina::from_celsius(c));
            std::printf("-> %s\n", culina::status_name(status));
        } else if (line.rfind("set-speed ", 0) == 0) {
            const auto dial = static_cast<std::uint8_t>(std::strtoul(line.c_str() + 10, nullptr, 10));
            const auto status = client.set_motor(static_cast<culina::Rpm>(dial * 1070),
                                                 culina::c1link::kRampNormal);
            std::printf("-> %s\n", culina::status_name(status));
        } else if (line == "tare") {
            std::printf("-> %s\n", culina::status_name(client.tare()));
        } else if (line == "stop") {
            std::printf("-> %s\n", culina::status_name(client.motor_stop()));
        } else if (!line.empty()) {
            std::printf("unknown command\n");
        }
    }

    g_quit.store(true);
    pumper.join();
    return 0;
}
