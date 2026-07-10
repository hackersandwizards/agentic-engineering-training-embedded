#include "common/crc16.h"

namespace culina {

std::uint16_t crc16_ccitt(const std::uint8_t* data, std::size_t len, std::uint16_t seed) {
    std::uint16_t crc = seed;
    for (std::size_t i = 0; i < len; ++i) {
        crc = static_cast<std::uint16_t>(static_cast<unsigned>(crc) ^
                                         (static_cast<unsigned>(data[i]) << 8u));
        for (int bit = 0; bit < 8; ++bit) {
            if ((crc & 0x8000u) != 0) {
                const auto shifted =
                    static_cast<std::uint16_t>(static_cast<std::uint32_t>(crc) << 1u);
                crc = static_cast<std::uint16_t>(shifted ^ std::uint16_t{0x1021});
            } else {
                crc = static_cast<std::uint16_t>(static_cast<std::uint32_t>(crc) << 1u);
            }
        }
    }
    return crc;
}

} // namespace culina
