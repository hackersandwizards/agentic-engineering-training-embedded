#include "sim/in_memory_transport.h"
#include "sim/sim_board.h"

#include <gtest/gtest.h>

namespace {

using namespace culina;
using namespace culina::sim;

TEST(SimBoard, BoilsWaterThroughTheHal) {
    SimBoard board;
    board.add_mass(500.0f);
    board.heater().set_power_w(1000.0f);
    std::uint32_t elapsed_s = 0;
    while (board.true_temperature_c() < 100.0f && elapsed_s < 600) {
        board.step_ms(1000);
        ++elapsed_s;
    }
    EXPECT_GE(board.true_temperature_c(), 100.0f);

    const auto reading = board.temp_sensor().read_deci_celsius();
    ASSERT_TRUE(reading.is_ok());
    EXPECT_NEAR(to_celsius(reading.value()), board.true_temperature_c(), 1.0f);
}

TEST(SimBoard, LockedLidRefusesToOpen) {
    SimBoard board;
    board.lid().set_lock(true);
    board.open_lid();
    EXPECT_TRUE(board.lid_closed());
    board.lid().set_lock(false);
    board.open_lid();
    EXPECT_FALSE(board.lid_closed());
}

TEST(SimBoard, WatchdogTripsWhenStarved) {
    SimBoard board;
    board.app_watchdog().feed();
    board.step_ms(400);
    EXPECT_FALSE(board.watchdog_tripped());
    board.app_watchdog().feed();
    board.step_ms(400);
    EXPECT_FALSE(board.watchdog_tripped());
    board.step_ms(200);
    EXPECT_TRUE(board.watchdog_tripped());
}

TEST(SimBoard, ClockOnlyMovesWhenStepped) {
    SimBoard board;
    const Micros before = board.clock().now_us();
    EXPECT_EQ(board.clock().now_us(), before);
    board.step_ms(5);
    EXPECT_EQ(board.clock().now_us(), before + 5000u);
}

TEST(InMemoryTransport, DeliversBytesInOrderBothWays) {
    InMemoryTransport transport;
    const std::uint8_t hello[] = {0x01, 0x02, 0x03};
    ASSERT_EQ(transport.app_side().write(hello, sizeof(hello)), sizeof(hello));

    std::uint8_t byte = 0;
    for (std::uint8_t expected : hello) {
        ASSERT_TRUE(transport.mcu_side().read(&byte));
        EXPECT_EQ(byte, expected);
    }
    EXPECT_FALSE(transport.mcu_side().read(&byte));

    const std::uint8_t reply[] = {0xAA};
    ASSERT_EQ(transport.mcu_side().write(reply, 1u), 1u);
    ASSERT_TRUE(transport.app_side().read(&byte));
    EXPECT_EQ(byte, 0xAA);
}

TEST(InMemoryTransport, BoundedCapacity) {
    InMemoryTransport transport;
    std::uint8_t chunk[512];
    for (std::size_t i = 0; i < sizeof(chunk); ++i) {
        chunk[i] = static_cast<std::uint8_t>(i);
    }
    std::size_t accepted = 0;
    for (int i = 0; i < 20; ++i) {
        accepted += transport.app_side().write(chunk, sizeof(chunk));
    }
    EXPECT_LT(accepted, 20u * sizeof(chunk));
    EXPECT_GT(accepted, 3000u);
}

} // namespace
