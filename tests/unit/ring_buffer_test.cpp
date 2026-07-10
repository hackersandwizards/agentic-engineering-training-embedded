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
