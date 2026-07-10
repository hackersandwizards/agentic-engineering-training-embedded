#include "protocol/frame_parser.h"
#include "protocol/frame_writer.h"

#include <gtest/gtest.h>

#include <cstring>

namespace {

using namespace culina::c1link;

std::size_t make_frame(std::uint8_t* buf, std::size_t cap, MsgId id, std::uint8_t seq,
                       const std::uint8_t* payload, std::uint16_t len,
                       FrameType type = FrameType::Request) {
    return write_frame(buf, cap, type, seq, id, payload, len);
}

TEST(FrameParser, RoundTripsAWrittenFrame) {
    const std::uint8_t payload[] = {0x10, 0x27, 0x02}; // 10000 rpm, ramp profile 2
    std::uint8_t wire[kMaxFrameSize];
    const std::size_t n =
        make_frame(wire, sizeof(wire), MsgId::MotorSetTarget, 7, payload, sizeof(payload));
    ASSERT_GT(n, 0u);

    FrameParser parser;
    Frame frame;
    bool complete = false;
    for (std::size_t i = 0; i < n; ++i) {
        complete = parser.feed(wire[i], &frame);
    }
    ASSERT_TRUE(complete);
    EXPECT_EQ(frame.type, FrameType::Request);
    EXPECT_EQ(frame.seq, 7);
    EXPECT_EQ(frame.msg_id, MsgId::MotorSetTarget);
    ASSERT_EQ(frame.payload_len, sizeof(payload));
    EXPECT_EQ(std::memcmp(frame.payload, payload, sizeof(payload)), 0);
}

TEST(FrameParser, ZeroLengthPayload) {
    std::uint8_t wire[kMaxFrameSize];
    const std::size_t n = make_frame(wire, sizeof(wire), MsgId::Ping, 1, nullptr, 0);
    ASSERT_GT(n, 0u);

    FrameParser parser;
    Frame frame;
    bool complete = false;
    for (std::size_t i = 0; i < n; ++i) {
        complete = parser.feed(wire[i], &frame);
    }
    ASSERT_TRUE(complete);
    EXPECT_EQ(frame.msg_id, MsgId::Ping);
    EXPECT_EQ(frame.payload_len, 0u);
}

TEST(FrameParser, IgnoresLeadingNoise) {
    const std::uint8_t noise[] = {0x00, 0x13, 0x37, 0xFF};
    std::uint8_t wire[kMaxFrameSize];
    const std::size_t n = make_frame(wire, sizeof(wire), MsgId::Ping, 2, nullptr, 0);

    FrameParser parser;
    Frame frame;
    for (std::uint8_t b : noise) {
        EXPECT_FALSE(parser.feed(b, &frame));
    }
    bool complete = false;
    for (std::size_t i = 0; i < n; ++i) {
        complete = parser.feed(wire[i], &frame);
    }
    EXPECT_TRUE(complete);
}

TEST(FrameParser, RejectsCorruptedPayload) {
    const std::uint8_t payload[] = {0x64, 0x00};
    std::uint8_t wire[kMaxFrameSize];
    const std::size_t n =
        make_frame(wire, sizeof(wire), MsgId::HeaterSetTarget, 3, payload, sizeof(payload));
    wire[kHeaderSize] ^= 0xFF; // flip a payload byte

    FrameParser parser;
    Frame frame;
    bool complete = false;
    for (std::size_t i = 0; i < n; ++i) {
        complete = parser.feed(wire[i], &frame);
    }
    EXPECT_FALSE(complete);

    // A following intact frame still gets through.
    const std::size_t m = make_frame(wire, sizeof(wire), MsgId::Ping, 4, nullptr, 0);
    for (std::size_t i = 0; i < m; ++i) {
        complete = parser.feed(wire[i], &frame);
    }
    EXPECT_TRUE(complete);
    EXPECT_EQ(frame.msg_id, MsgId::Ping);
}

TEST(FrameWriter, RefusesOversizedPayload) {
    std::uint8_t payload[kMaxPayload + 1] = {};
    std::uint8_t wire[kMaxFrameSize + 8];
    EXPECT_EQ(write_frame(wire, sizeof(wire), FrameType::Request, 0, MsgId::Ping, payload,
                          kMaxPayload + 1),
              0u);
}

TEST(FieldHelpers, RoundTripLittleEndian) {
    std::uint8_t buf[4];
    put_u16(buf, 0xBEEF);
    EXPECT_EQ(buf[0], 0xEF);
    EXPECT_EQ(buf[1], 0xBE);
    EXPECT_EQ(get_u16(buf), 0xBEEF);

    put_i32(buf, -123456);
    EXPECT_EQ(get_i32(buf), -123456);

    put_u32(buf, 0x0A0B0C0Du);
    EXPECT_EQ(buf[0], 0x0D);
    EXPECT_EQ(get_u32(buf), 0x0A0B0C0Du);
}

TEST(Telemetry, EncodesLittleEndianFields) {
    TelemetryData data;
    data.tick = 100000;
    data.deci_celsius = 985; // 98.5 C
    data.rpm = 4300;
    data.grams = 512;
    data.flags = kFlagLidClosed | kFlagHeaterOn;

    std::uint8_t buf[kTelemetryPayloadSize];
    encode_telemetry(data, buf);
    EXPECT_EQ(get_u32(buf), 100000u);
    EXPECT_EQ(get_i16(buf + 4), 985);
    EXPECT_EQ(get_u16(buf + 6), 4300u);
    EXPECT_EQ(get_i32(buf + 8), 512);
    EXPECT_EQ(buf[12], kFlagLidClosed | kFlagHeaterOn);
}

} // namespace
