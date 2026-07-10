// Safety MCU as its own process: owns the simulated board hardware and runs
// the 1 ms control tick in real time. Pair with culina_app over the socket.

#include "common/parse_number.h"
#include "mcu/safety_mcu.h"
#include "sim/sim_board.h"
#include "sim/socket_transport.h"

#include <chrono>
#include <cstdio>
#include <cstring>
#include <thread>

int main(int argc, char** argv) {
    const char* socket_path = "/tmp/c1link.sock";
    float water_g = 0.0f;

    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "--socket") == 0 && i + 1 < argc) {
            socket_path = argv[++i];
        } else if (std::strcmp(argv[i], "--water") == 0 && i + 1 < argc) {
            if (!culina::parse_float(argv[++i], 0.0f, 2200.0f, &water_g)) {
                std::fprintf(stderr, "invalid water mass\n");
                return 2;
            }
        } else {
            std::fprintf(stderr, "usage: %s [--socket path] [--water grams]\n", argv[0]);
            return 2;
        }
    }

    culina::sim::SimBoard board;
    if (water_g > 0.0f) {
        board.add_mass(water_g);
    }
    auto uart = culina::sim::SocketTransport::listen_on(socket_path);
    if (!uart.valid()) {
        return 1;
    }

    culina::mcu::SafetyMcu::Hardware hw;
    hw.motor = &board.motor();
    hw.heater = &board.heater();
    hw.temp_sensor = &board.temp_sensor();
    hw.scale = &board.scale();
    hw.lid = &board.lid();
    culina::mcu::SafetyMcu mcu(hw, &uart, &board.clock());

    std::printf("culina-mcu: listening on %s (%.0f g preloaded)\n", socket_path,
                static_cast<double>(water_g));

    auto next_status = std::chrono::steady_clock::now();
    while (true) {
        board.step_ms(1);
        mcu.tick_1ms();

        const auto now = std::chrono::steady_clock::now();
        if (now >= next_status) {
            next_status = now + std::chrono::seconds(2);
            std::printf("[mcu] %6.1f C  heater %4.0f W  motor %5u rpm  link:%s\n",
                        static_cast<double>(board.true_temperature_c()),
                        static_cast<double>(board.heater().power_w()), board.motor().rpm(),
                        uart.connected() ? "up" : "DOWN");
            std::fflush(stdout);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
