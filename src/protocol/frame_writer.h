#pragma once

#include "protocol/c1link.h"

namespace culina::c1link {

// Serializes one frame into the caller's buffer. Returns the number of bytes
// written, or 0 when the payload is oversized or the buffer too small.
std::size_t write_frame(std::uint8_t* out, std::size_t out_cap, FrameType type, std::uint8_t seq,
                        MsgId msg_id, const std::uint8_t* payload, std::uint16_t payload_len);

} // namespace culina::c1link
