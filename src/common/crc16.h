#pragma once

#include <cstddef>
#include <cstdint>

namespace culina {

// CRC16-CCITT (polynomial 0x1021, initial value 0xFFFF), as used by C1-Link.
std::uint16_t crc16_ccitt(const std::uint8_t* data, std::size_t len, std::uint16_t seed = 0xFFFF);

} // namespace culina
