#include "app/application_runtime.h"
#include "sim/in_memory_transport.h"
#include "sim/sim_board.h"

#include <gtest/gtest.h>

namespace culina::app {
namespace {

class CountingWatchdog final : public hal::IWatchdog {
public:
    void feed() override { ++feeds; }
    Millis timeout_ms() const override { return 500; }

    int feeds = 0;
};

TEST(ApplicationRuntime, ServicesControllerEveryTenMilliseconds) {
    sim::SimClock clock;
    sim::InMemoryTransport transport;
    CountingWatchdog watchdog;
    ApplicationRuntime runtime(&transport.app_side(), &clock, &watchdog);

    for (int i = 0; i < 9; ++i) {
        clock.advance_us(1000);
        runtime.tick_1ms();
    }
    EXPECT_EQ(watchdog.feeds, 0);

    clock.advance_us(1000);
    runtime.tick_1ms();
    EXPECT_EQ(watchdog.feeds, 1);
}

TEST(ApplicationRuntime, OwnsTheApplicationFacingServices) {
    sim::SimBoard board;
    sim::InMemoryTransport transport;
    ApplicationRuntime runtime(&transport.app_side(), &board.clock(), &board.app_watchdog());

    EXPECT_FALSE(runtime.telemetry().has_data());
    EXPECT_EQ(runtime.recipes().count(), 0u);
    EXPECT_FALSE(runtime.ota().busy());
}

} // namespace
} // namespace culina::app
