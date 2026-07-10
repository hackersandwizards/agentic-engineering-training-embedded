#include "common/parse_number.h"

#include <gtest/gtest.h>

namespace {

TEST(ParseNumber, AcceptsBoundedValues) {
    float decimal = 0.0f;
    std::uint32_t integer = 0;
    EXPECT_TRUE(culina::parse_float("63.5", 37.0f, 90.0f, &decimal));
    EXPECT_FLOAT_EQ(decimal, 63.5f);
    EXPECT_TRUE(culina::parse_u32("10", 10, &integer));
    EXPECT_EQ(integer, 10u);
}

TEST(ParseNumber, RejectsNonFiniteOverflowAndTrailingInput) {
    float decimal = 0.0f;
    std::uint32_t integer = 0;
    EXPECT_FALSE(culina::parse_float("nan", 0.0f, 160.0f, &decimal));
    EXPECT_FALSE(culina::parse_float("65C", 0.0f, 160.0f, &decimal));
    EXPECT_FALSE(culina::parse_u32("-1", 10, &integer));
    EXPECT_FALSE(culina::parse_u32("11", 10, &integer));
    EXPECT_FALSE(culina::parse_u32("999999999999999", 10, &integer));
}

} // namespace
