#pragma once

#include <cstddef>
#include <cstdint>

namespace culina::c1link {

// C1-Link wire format. See docs/c1link-protocol.md for the full specification.
//
//   0   2  sync 0xA5 0x5A
//   2   1  version (high nibble) | flags (low nibble)
//   3   1  frame type
//   4   1  sequence number (echoed in responses)
//   5   1  message id
//   6   2  payload length, little-endian
//   8   N  payload, little-endian fields
//   8+N 2  CRC16-CCITT, little-endian

constexpr std::uint8_t kSync0 = 0xA5;
constexpr std::uint8_t kSync1 = 0x5A;
constexpr std::uint8_t kVersion = 0x10;
constexpr std::size_t kMaxPayload = 250;
constexpr std::size_t kHeaderSize = 8;
constexpr std::size_t kCrcSize = 2;
constexpr std::size_t kMaxFrameSize = kHeaderSize + kMaxPayload + kCrcSize;

enum class FrameType : std::uint8_t {
    Request = 0x01,
    Response = 0x02,
    Telemetry = 0x03,
    Nack = 0x04,
};

enum class MsgId : std::uint8_t {
    Ping = 0x01,
    GetVersion = 0x02,
    MotorSetTarget = 0x10, // payload: rpm u16, ramp-profile u8
    MotorStop = 0x11,
    HeaterSetTarget = 0x20, // payload: deci-celsius i16
    HeaterOff = 0x21,
    ScaleTare = 0x30,
    ScaleRead = 0x31, // response payload: grams i32
    LidLock = 0x40,
    LidUnlock = 0x41,
    Telemetry = 0x80, // payload: tick u32, deci-celsius i16, rpm u16, grams i32, flags u8
    Fault = 0x81,     // payload: fault code u8
};

// Telemetry flags bitmask.
constexpr std::uint8_t kFlagLidClosed = 0x01;
constexpr std::uint8_t kFlagLidLocked = 0x02;
constexpr std::uint8_t kFlagHeaterOn = 0x04;
constexpr std::uint8_t kFlagMotorStalled = 0x08;

enum class FaultCode : std::uint8_t {
    None = 0,
    Overtemp = 1,
    MotorStall = 2,
    SensorFailure = 3,
};

struct Frame {
    FrameType type = FrameType::Request;
    std::uint8_t seq = 0;
    MsgId msg_id = MsgId::Ping;
    std::uint16_t payload_len = 0;
    std::uint8_t payload[kMaxPayload] = {};
};

constexpr std::size_t kTelemetryPayloadSize = 13;

struct TelemetryData {
    std::uint32_t tick = 0;
    std::int16_t deci_celsius = 0;
    std::uint16_t rpm = 0;
    std::int32_t grams = 0;
    std::uint8_t flags = 0;
};

// Little-endian field helpers.
inline void put_u16(std::uint8_t* p, std::uint16_t v) {
    p[0] = static_cast<std::uint8_t>(v & 0xFFu);
    p[1] = static_cast<std::uint8_t>(v >> 8);
}

inline std::uint16_t get_u16(const std::uint8_t* p) {
    return static_cast<std::uint16_t>(p[0] | (static_cast<std::uint16_t>(p[1]) << 8));
}

inline void put_i16(std::uint8_t* p, std::int16_t v) {
    put_u16(p, static_cast<std::uint16_t>(v));
}

inline std::int16_t get_i16(const std::uint8_t* p) {
    return static_cast<std::int16_t>(get_u16(p));
}

inline void put_u32(std::uint8_t* p, std::uint32_t v) {
    p[0] = static_cast<std::uint8_t>(v & 0xFFu);
    p[1] = static_cast<std::uint8_t>((v >> 8) & 0xFFu);
    p[2] = static_cast<std::uint8_t>((v >> 16) & 0xFFu);
    p[3] = static_cast<std::uint8_t>(v >> 24);
}

inline std::uint32_t get_u32(const std::uint8_t* p) {
    return static_cast<std::uint32_t>(p[0]) | (static_cast<std::uint32_t>(p[1]) << 8) |
           (static_cast<std::uint32_t>(p[2]) << 16) | (static_cast<std::uint32_t>(p[3]) << 24);
}

inline void put_i32(std::uint8_t* p, std::int32_t v) {
    put_u32(p, static_cast<std::uint32_t>(v));
}

inline std::int32_t get_i32(const std::uint8_t* p) {
    return static_cast<std::int32_t>(get_u32(p));
}

inline void encode_telemetry(const TelemetryData& data, std::uint8_t* out) {
    put_u32(out, data.tick);
    put_i16(out + 4, data.deci_celsius);
    put_u16(out + 6, data.rpm);
    put_i32(out + 8, data.grams);
    out[12] = data.flags;
}

} // namespace culina::c1link
