#include "app/mcu_client.h"
#include "mcu/safety_mcu.h"
#include "sim/in_memory_transport.h"
#include "sim/sim_board.h"
#include "support/flaky_transport.h"

#include <gtest/gtest.h>

namespace {

using namespace culina;
using namespace culina::c1link;

struct ClientFixture {
    ClientFixture() {
        mcu::SafetyMcu::Hardware hw;
        hw.motor = &board.motor();
        hw.heater = &board.heater();
        hw.temp_sensor = &board.temp_sensor();
        hw.scale = &board.scale();
        hw.lid = &board.lid();
        mcu.emplace(hw, &transport.mcu_side(), &board.clock());
    }

    void run_ms(std::uint32_t ms) {
        for (std::uint32_t i = 0; i < ms; ++i) {
            board.step_ms(1);
            mcu->tick_1ms();
            client.poll();
        }
    }

    sim::SimBoard board;
    sim::InMemoryTransport transport;
    std::optional<mcu::SafetyMcu> mcu;
    app::TelemetryStore store;
    app::McuClient client{&transport.app_side(), &board.clock(), &store};
};

TEST(McuClient, HeaterCommandGetsAResponse) {
    ClientFixture fix;
    ASSERT_EQ(fix.client.set_heater(from_celsius(65.0f)), Status::Ok);
    EXPECT_TRUE(fix.client.awaiting_response());
    fix.run_ms(5);
    Frame response;
    ASSERT_TRUE(fix.client.take_response(&response));
    EXPECT_EQ(response.type, FrameType::Response);
    EXPECT_EQ(response.msg_id, MsgId::HeaterSetTarget);
    EXPECT_FALSE(fix.client.awaiting_response());
}

TEST(McuClient, SecondRequestWhilePendingIsRefused) {
    ClientFixture fix;
    ASSERT_EQ(fix.client.set_heater(from_celsius(65.0f)), Status::Ok);
    EXPECT_EQ(fix.client.motor_stop(), Status::NotReady);
}

TEST(McuClient, TelemetryLandsInTheStore) {
    ClientFixture fix;
    fix.run_ms(1000);
    EXPECT_GE(fix.store.size(), 95u);
    EXPECT_NEAR(to_celsius(fix.store.latest().deci_celsius), 20.0f, 1.0f);
    EXPECT_EQ(fix.store.latest().rpm, 0u);
    EXPECT_TRUE((fix.store.latest().flags & kFlagLidClosed) != 0);
}

TEST(McuClient, MotorSpinsUpAfterGrantedRequest) {
    ClientFixture fix;
    ASSERT_EQ(fix.client.set_motor(5000, c1link::kRampFast), Status::Ok);
    fix.run_ms(5);
    Frame response;
    ASSERT_TRUE(fix.client.take_response(&response));
    ASSERT_EQ(response.payload_len, 2u);
    EXPECT_EQ(get_u16(response.payload), 5000u);

    fix.run_ms(2500);
    EXPECT_NEAR(static_cast<float>(fix.store.latest().rpm), 5000.0f, 400.0f);
}

TEST(McuClient, RetriesALostRequest) {
    sim::SimBoard board;
    sim::InMemoryTransport transport;
    culina::testing::FlakyTransport flaky(&transport.app_side());

    mcu::SafetyMcu::Hardware hw;
    hw.motor = &board.motor();
    hw.heater = &board.heater();
    hw.temp_sensor = &board.temp_sensor();
    hw.scale = &board.scale();
    hw.lid = &board.lid();
    mcu::SafetyMcu safety_mcu(hw, &transport.mcu_side(), &board.clock());

    app::TelemetryStore store;
    app::McuClient client(&flaky, &board.clock(), &store);

    flaky.drop_next_write();
    ASSERT_EQ(client.set_heater(from_celsius(80.0f)), Status::Ok);

    Frame response;
    bool got_response = false;
    for (int i = 0; i < 200 && !got_response; ++i) {
        board.step_ms(1);
        safety_mcu.tick_1ms();
        client.poll();
        got_response = client.take_response(&response);
    }
    ASSERT_TRUE(got_response);
    EXPECT_EQ(response.msg_id, MsgId::HeaterSetTarget);
    EXPECT_FALSE(client.awaiting_response());
}

TEST(McuClient, TelemetryWeightMatchesTheBowl) {
    ClientFixture fix;
    fix.board.add_mass(512.0f);
    fix.run_ms(500);
    EXPECT_NEAR(static_cast<float>(fix.store.latest().grams), 512.0f, 6.0f);
}

TEST(McuClient, FaultFrameIsSurfaced) {
    ClientFixture fix;
    fix.board.set_ambient_c(175.0f);
    ASSERT_EQ(fix.client.set_heater(1600), Status::Ok);
    fix.run_ms(180000);
    EXPECT_EQ(fix.client.last_fault(), FaultCode::Overtemp);
}

} // namespace
