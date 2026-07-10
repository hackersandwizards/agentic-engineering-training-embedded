#pragma once

#include <cstddef>
#include <cstdint>

namespace culina {

// C1-Link uses CRC16-CCITT with polynomial 0x1021 and initial value 0xFFFF.
std::uint16_t crc16_ccitt(const std::uint8_t* data, std::size_t len, std::uint16_t seed = 0xFFFF);

} // namespace culina
