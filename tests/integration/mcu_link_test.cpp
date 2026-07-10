#include "support/sim_fixture.h"

#include <gtest/gtest.h>

namespace {

using namespace culina;
using namespace culina::c1link;
using culina::testing::McuFixture;

TEST(McuLink, RespondsToPing) {
    McuFixture fix;
    fix.send_request(MsgId::Ping, nullptr, 0);
    fix.run_ms(5);
    ASSERT_EQ(fix.responses().size(), 1u);
    EXPECT_EQ(fix.responses()[0].msg_id, MsgId::Ping);
    EXPECT_EQ(fix.responses()[0].type, FrameType::Response);
    EXPECT_EQ(fix.responses()[0].seq, 0);
}

TEST(McuLink, HeatsWaterToTarget) {
    McuFixture fix;
    fix.board().add_mass(500.0f);
    std::uint8_t target[2];
    put_i16(target, 1000); // 100.0 C
    fix.send_request(MsgId::HeaterSetTarget, target, sizeof(target));
    fix.run_ms(400000); // just under 7 simulated minutes
    EXPECT_GE(fix.board().true_temperature_c(), 99.0f);
    EXPECT_LE(fix.board().true_temperature_c(), 106.0f);
    EXPECT_NEAR(to_celsius(fix.last_telemetry().deci_celsius), fix.board().true_temperature_c(),
                1.5f);
}

TEST(McuLink, ClampsSpeedWithUnlockedLid) {
    McuFixture fix;
    std::uint8_t req[3];
    put_u16(req, 9000);
    req[2] = c1link::kRampFast;
    fix.send_request(MsgId::MotorSetTarget, req, sizeof(req));
    fix.run_ms(5);
    ASSERT_EQ(fix.responses().size(), 1u);
    ASSERT_EQ(fix.responses()[0].payload_len, 2u);
    EXPECT_EQ(get_u16(fix.responses()[0].payload), 6400u);
}

TEST(McuLink, LidOpeningWhileRunningCutsSpeed) {
    McuFixture fix;
    std::uint8_t req[3];
    put_u16(req, 5000);
    req[2] = c1link::kRampFast;
    fix.send_request(MsgId::MotorSetTarget, req, sizeof(req));
    fix.run_ms(3000);
    EXPECT_GT(fix.last_telemetry().rpm, 4000u);

    fix.board().open_lid();
    fix.run_ms(3000);
    EXPECT_LE(fix.last_telemetry().rpm, 600u);
}

TEST(McuLink, OvertempTripsTheHeaterFault) {
    McuFixture fix;
    std::uint8_t target[2];
    put_i16(target, 1200);
    fix.send_request(MsgId::HeaterSetTarget, target, sizeof(target));
    fix.board().set_ambient_c(175.0f); // hot environment drives the sensor past the cutoff
    fix.run_ms(300000);
    EXPECT_EQ(fix.last_fault(), FaultCode::Overtemp);
    EXPECT_EQ(fix.board().heater().power_w(), 0.0f);
}

TEST(McuLink, TareThenRead) {
    McuFixture fix;
    fix.board().add_mass(300.0f);
    fix.run_ms(5);

    fix.send_request(MsgId::ScaleRead, nullptr, 0);
    fix.run_ms(5);
    ASSERT_EQ(fix.responses().size(), 1u);
    EXPECT_NEAR(static_cast<float>(get_i32(fix.responses()[0].payload)), 300.0f, 5.0f);

    fix.send_request(MsgId::ScaleTare, nullptr, 0);
    fix.run_ms(5);
    fix.board().add_mass(200.0f);
    fix.send_request(MsgId::ScaleRead, nullptr, 0);
    fix.run_ms(5);
    ASSERT_EQ(fix.responses().size(), 3u);
    EXPECT_NEAR(static_cast<float>(get_i32(fix.responses()[2].payload)), 200.0f, 5.0f);
}

TEST(McuLink, TelemetryStreamsAtOneHundredHertz) {
    McuFixture fix;
    fix.run_ms(1000);
    EXPECT_GE(fix.telemetry_count(), 95u);
    EXPECT_LE(fix.telemetry_count(), 105u);
    EXPECT_TRUE((fix.last_telemetry().flags & kFlagLidClosed) != 0);
}

TEST(McuLink, InterlocksKeepRunningWhileAFrameTrickles) {
    McuFixture fix;
    std::uint8_t req[3];
    put_u16(req, 5000);
    req[2] = c1link::kRampFast;
    fix.send_request(MsgId::MotorSetTarget, req, sizeof(req));
    fix.run_ms(3000);
    ASSERT_GT(fix.last_telemetry().rpm, 4000u);

    // A valid header announcing a 200-byte payload, then one byte per
    // millisecond. The lid opens mid-frame; the cap and telemetry must not
    // wait for the frame to finish.
    const std::uint8_t slow_header[] = {kSync0, kSync1, kVersion, 0x01, 0x09, 0x01, 200, 0x00};
    fix.write_raw(slow_header, sizeof(slow_header));
    fix.board().open_lid();
    for (int i = 0; i < 30; ++i) {
        const std::uint8_t filler = 0x55;
        fix.write_raw(&filler, 1);
        fix.run_ms(1);
    }
    EXPECT_LE(fix.last_telemetry().rpm, 4800u); // already decelerating

    for (int i = 0; i < 170; ++i) {
        const std::uint8_t filler = 0x55;
        fix.write_raw(&filler, 1);
        fix.run_ms(1);
    }
    fix.run_ms(2000);
    EXPECT_LE(fix.last_telemetry().rpm, 600u);
}

TEST(McuLink, LidPauseDoesNotCauseAnOvershootAfterwards) {
    McuFixture fix;
    fix.board().add_mass(1000.0f);
    std::uint8_t target[2];
    put_i16(target, 650); // 65.0 C
    fix.send_request(MsgId::HeaterSetTarget, target, sizeof(target));
    fix.run_ms(500000); // settle at the setpoint

    fix.board().open_lid();
    fix.run_ms(180000); // three minutes with the heater interlocked off
    fix.board().close_lid();

    float max_c = 0.0f;
    for (int i = 0; i < 400; ++i) {
        fix.run_ms(1000);
        const float c = to_celsius(fix.last_telemetry().deci_celsius);
        max_c = c > max_c ? c : max_c;
    }
    EXPECT_LE(max_c, 67.0f); // a 65.0 hold may transiently touch the mid-66s
}

TEST(McuLink, BurstNeedsALockedLid) {
    McuFixture fix;
    std::uint8_t req[3];
    put_u16(req, 10700);
    req[2] = c1link::kRampBurst;
    fix.send_request(MsgId::MotorSetTarget, req, sizeof(req));
    fix.run_ms(5);
    ASSERT_EQ(fix.responses().size(), 1u);
    EXPECT_EQ(fix.responses()[0].type, FrameType::Nack);

    fix.send_request(MsgId::LidLock, nullptr, 0);
    fix.run_ms(5);
    fix.send_request(MsgId::MotorSetTarget, req, sizeof(req));
    fix.run_ms(1500);
    EXPECT_GT(fix.last_telemetry().rpm, 9500u);
}

} // namespace
