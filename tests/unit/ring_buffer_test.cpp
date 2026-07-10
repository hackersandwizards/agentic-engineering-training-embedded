#include "common/ring_buffer.h"

#include <gtest/gtest.h>

namespace {

using culina::RingBuffer;

TEST(RingBuffer, StartsEmpty) {
    RingBuffer<8> ring;
    EXPECT_TRUE(ring.empty());
    EXPECT_EQ(ring.size(), 0u);
    std::uint8_t byte = 0;
    EXPECT_FALSE(ring.pop(&byte));
}

TEST(RingBuffer, PushPopPreservesOrder) {
    RingBuffer<8> ring;
    for (std::uint8_t i = 0; i < 5; ++i) {
        EXPECT_TRUE(ring.push(i));
    }
    EXPECT_EQ(ring.size(), 5u);
    for (std::uint8_t i = 0; i < 5; ++i) {
        std::uint8_t byte = 0;
        EXPECT_TRUE(ring.pop(&byte));
        EXPECT_EQ(byte, i);
    }
    EXPECT_TRUE(ring.empty());
}

TEST(RingBuffer, UsesTheFullCapacity) {
    RingBuffer<8> ring;
    for (std::uint8_t i = 0; i < 8; ++i) {
        EXPECT_TRUE(ring.push(i)) << "slot " << static_cast<int>(i) << " refused";
    }
    EXPECT_FALSE(ring.push(99));
    EXPECT_EQ(ring.size(), 8u);
    for (std::uint8_t i = 0; i < 8; ++i) {
        std::uint8_t byte = 0;
        ASSERT_TRUE(ring.pop(&byte));
        EXPECT_EQ(byte, i);
    }
}

TEST(RingBuffer, FullCapacityAfterWraparound) {
    RingBuffer<4> ring;
    std::uint8_t byte = 0;
    // Shift head/tail off zero first, then fill completely.
    ASSERT_TRUE(ring.push(1));
    ASSERT_TRUE(ring.pop(&byte));
    for (std::uint8_t i = 0; i < 4; ++i) {
        EXPECT_TRUE(ring.push(i));
    }
    EXPECT_EQ(ring.size(), 4u);
}

TEST(RingBuffer, WrapsAround) {
    RingBuffer<4> ring;
    std::uint8_t byte = 0;
    for (std::uint8_t round = 0; round < 10; ++round) {
        EXPECT_TRUE(ring.push(round));
        EXPECT_TRUE(ring.push(static_cast<std::uint8_t>(round + 100)));
        EXPECT_TRUE(ring.pop(&byte));
        EXPECT_EQ(byte, round);
        EXPECT_TRUE(ring.pop(&byte));
        EXPECT_EQ(byte, static_cast<std::uint8_t>(round + 100));
    }
    EXPECT_TRUE(ring.empty());
}

} // namespace
