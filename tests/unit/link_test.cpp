#include "protocol/link.h"
#include "sim/in_memory_transport.h"
#include "sim/sim_clock.h"

#include <gtest/gtest.h>

namespace {

using namespace culina;
using namespace culina::c1link;

TEST(Link, SendsFramesTheOtherSideCanParse) {
    sim::InMemoryTransport transport;
    sim::SimClock clock;
    Link app(&transport.app_side(), &clock);
    Link mcu(&transport.mcu_side(), &clock);

    const std::uint8_t payload[] = {0xE8, 0x03}; // 100.0 C
    ASSERT_EQ(app.send(FrameType::Request, 9, MsgId::HeaterSetTarget, payload, sizeof(payload)),
              Status::Ok);

    Frame frame;
    ASSERT_TRUE(mcu.poll(&frame));
    EXPECT_EQ(frame.msg_id, MsgId::HeaterSetTarget);
    EXPECT_EQ(frame.seq, 9);
    ASSERT_EQ(frame.payload_len, 2u);
    EXPECT_EQ(get_i16(frame.payload), 1000);
    EXPECT_FALSE(mcu.poll(&frame));
}

TEST(Link, RefusesOversizedPayloads) {
    sim::InMemoryTransport transport;
    sim::SimClock clock;
    Link link(&transport.app_side(), &clock);
    std::uint8_t payload[kMaxPayload + 1] = {};
    EXPECT_EQ(link.send(FrameType::Request, 0, MsgId::Ping, payload, sizeof(payload)),
              Status::InvalidArgument);
    std::uint8_t byte = 0;
    EXPECT_FALSE(transport.mcu_side().read(&byte));
}

TEST(Link, DropsAStalledPartialFrame) {
    sim::InMemoryTransport transport;
    sim::SimClock clock;
    Link app(&transport.app_side(), &clock);
    Link mcu(&transport.mcu_side(), &clock);

    // Half a frame, then silence past the frame timeout.
    const std::uint8_t partial[] = {kSync0, kSync1, kVersion, 0x01, 0x00};
    transport.app_side().write(partial, sizeof(partial));
    Frame frame;
    EXPECT_FALSE(mcu.poll(&frame));

    clock.advance_us(ms_to_us(Link::kFrameTimeoutMs + 10));
    EXPECT_FALSE(mcu.poll(&frame));

    // A fresh frame afterwards parses normally.
    ASSERT_EQ(app.send(FrameType::Request, 1, MsgId::Ping, nullptr, 0), Status::Ok);
    ASSERT_TRUE(mcu.poll(&frame));
    EXPECT_EQ(frame.msg_id, MsgId::Ping);
}

} // namespace
