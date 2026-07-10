#include "common/crc16.h"

#include <gtest/gtest.h>

namespace {

TEST(Crc16, MatchesCcittFalseCheckValue) {
    // Standard check input for CRC-16/CCITT-FALSE.
    const std::uint8_t data[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    EXPECT_EQ(culina::crc16_ccitt(data, sizeof(data)), 0x29B1u);
}

TEST(Crc16, EmptyInputYieldsSeed) {
    EXPECT_EQ(culina::crc16_ccitt(nullptr, 0), 0xFFFFu);
}

TEST(Crc16, SeedChainsAcrossCalls) {
    const std::uint8_t data[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    std::uint16_t first = culina::crc16_ccitt(data, 4);
    std::uint16_t chained = culina::crc16_ccitt(data + 4, 5, first);
    EXPECT_EQ(chained, culina::crc16_ccitt(data, sizeof(data)));
}

} // namespace
