#include "protocol/frame_writer.h"

#include "common/crc16.h"

#include <cstring>

namespace culina::c1link {

std::size_t write_frame(std::uint8_t* out, std::size_t out_cap, FrameType type, std::uint8_t seq,
                        MsgId msg_id, const std::uint8_t* payload, std::uint16_t payload_len) {
    const std::size_t total = kHeaderSize + payload_len + kCrcSize;
    if (payload_len > kMaxPayload || out_cap < total) {
        return 0;
    }
    out[0] = kSync0;
    out[1] = kSync1;
    out[2] = kVersion;
    out[3] = static_cast<std::uint8_t>(type);
    out[4] = seq;
    out[5] = static_cast<std::uint8_t>(msg_id);
    put_u16(&out[6], payload_len);
    if (payload_len > 0) {
        std::memcpy(&out[kHeaderSize], payload, payload_len);
    }
    const std::uint16_t crc = crc16_ccitt(payload, payload_len);
    put_u16(&out[kHeaderSize + payload_len], crc);
    return total;
}

} // namespace culina::c1link
