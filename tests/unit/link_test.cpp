#include "protocol/frame_writer.h"
#include "protocol/link.h"
#include "sim/in_memory_transport.h"
#include "sim/sim_clock.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <deque>
#include <vector>

namespace {

using namespace culina;
using namespace culina::c1link;

class ChunkedUart : public hal::IUart {
public:
    std::size_t write(const std::uint8_t* data, std::size_t len) override {
        const std::size_t count = std::min<std::size_t>(3, len);
        bytes.insert(bytes.end(), data, data + count);
        return count;
    }

    bool read(std::uint8_t*) override { return false; }

    std::vector<std::uint8_t> bytes;
};

class DuplexUart : public hal::IUart {
public:
    DuplexUart(std::deque<std::uint8_t>* incoming, std::deque<std::uint8_t>* outgoing)
        : incoming_(incoming), outgoing_(outgoing) {}

    std::size_t write(const std::uint8_t* data, std::size_t len) override {
        ++writes_;
        if ((writes_ % 2u) != 0u) {
            return 0;
        }
        const std::size_t count = std::min<std::size_t>(3, len);
        outgoing_->insert(outgoing_->end(), data, data + count);
        return count;
    }

    bool read(std::uint8_t* out) override {
        if (incoming_->empty()) {
            return false;
        }
        *out = incoming_->front();
        incoming_->pop_front();
        return true;
    }

private:
    std::deque<std::uint8_t>* incoming_;
    std::deque<std::uint8_t>* outgoing_;
    std::size_t writes_ = 0;
};

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

TEST(Link, ContinuesPartialWritesWithoutCorruptingTheFrame) {
    ChunkedUart uart;
    sim::SimClock clock;
    Link link(&uart, &clock);
    const std::uint8_t payload[] = {1, 2, 3, 4, 5};

    ASSERT_EQ(link.send(FrameType::Request, 7, MsgId::MotorSetTarget, payload, sizeof(payload)),
              Status::Ok);
    EXPECT_EQ(link.send(FrameType::Request, 8, MsgId::Ping, nullptr, 0), Status::Ok);

    Frame ignored;
    for (int i = 0; i < 20; ++i) {
        link.poll(&ignored);
    }

    FrameParser parser;
    Frame frame;
    int completed = 0;
    bool first_frame_valid = false;
    for (std::uint8_t byte : uart.bytes) {
        if (parser.feed(byte, &frame)) {
            ++completed;
            if (frame.seq == 7 && frame.msg_id == MsgId::MotorSetTarget &&
                frame.payload_len == sizeof(payload)) {
                first_frame_valid =
                    std::equal(std::begin(payload), std::end(payload), frame.payload);
            }
        }
    }
    EXPECT_EQ(completed, 2);
    EXPECT_TRUE(first_frame_valid);
    EXPECT_EQ(frame.seq, 8);
    EXPECT_EQ(frame.msg_id, MsgId::Ping);
}

TEST(Link, ReceivesWhileBothSidesHaveBackpressuredTransmissions) {
    std::deque<std::uint8_t> app_to_mcu;
    std::deque<std::uint8_t> mcu_to_app;
    DuplexUart app_uart(&mcu_to_app, &app_to_mcu);
    DuplexUart mcu_uart(&app_to_mcu, &mcu_to_app);
    sim::SimClock clock;
    Link app(&app_uart, &clock);
    Link mcu(&mcu_uart, &clock);

    ASSERT_EQ(app.send(FrameType::Request, 1, MsgId::Ping, nullptr, 0), Status::Ok);
    ASSERT_EQ(mcu.send(FrameType::Response, 1, MsgId::Ping, nullptr, 0), Status::Ok);

    bool app_received = false;
    bool mcu_received = false;
    for (int i = 0; i < 20 && (!app_received || !mcu_received); ++i) {
        Frame frame;
        if (app.poll(&frame)) {
            app_received = frame.type == FrameType::Response && frame.msg_id == MsgId::Ping;
        }
        if (mcu.poll(&frame)) {
            mcu_received = frame.type == FrameType::Request && frame.msg_id == MsgId::Ping;
        }
    }

    EXPECT_TRUE(app_received);
    EXPECT_TRUE(mcu_received);
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

TEST(Link, InFlightFrameSurvivesMillisecondWraparound) {
    sim::InMemoryTransport transport;
    sim::SimClock clock;
    // Park the clock just before the 32-bit millisecond counter wraps, so the
    // frame deadline lands on the far side of the wrap.
    clock.advance_us((0xFFFFFFFFull - 20) * 1000);
    Link app(&transport.app_side(), &clock);
    Link mcu(&transport.mcu_side(), &clock);

    std::uint8_t wire[kMaxFrameSize];
    const std::size_t n =
        write_frame(wire, sizeof(wire), FrameType::Request, 3, MsgId::Ping, nullptr, 0);
    ASSERT_GT(n, 4u);

    // First half arrives, then a pause well inside the 50 ms frame timeout
    // that crosses the wrap, then the rest. The frame must still assemble.
    transport.app_side().write(wire, 4);
    Frame frame;
    EXPECT_FALSE(mcu.poll(&frame));

    clock.advance_us(ms_to_us(25));
    EXPECT_FALSE(mcu.poll(&frame));

    transport.app_side().write(wire + 4, n - 4);
    ASSERT_TRUE(mcu.poll(&frame));
    EXPECT_EQ(frame.msg_id, MsgId::Ping);
    (void)app;
}

} // namespace
