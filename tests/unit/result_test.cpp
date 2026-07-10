#include "common/result.h"

#include <gtest/gtest.h>

namespace {

using culina::Result;
using culina::Status;

TEST(Result, OkCarriesValue) {
    auto r = Result<int>::ok(42);
    ASSERT_TRUE(r.is_ok());
    EXPECT_EQ(r.value(), 42);
    EXPECT_EQ(r.status(), Status::Ok);
}

TEST(Result, ErrCarriesStatus) {
    auto r = Result<int>::err(Status::Timeout);
    EXPECT_FALSE(r.is_ok());
    EXPECT_EQ(r.status(), Status::Timeout);
}

TEST(Result, StatusNamesAreStable) {
    EXPECT_STREQ(culina::status_name(Status::Ok), "Ok");
    EXPECT_STREQ(culina::status_name(Status::CrcMismatch), "CrcMismatch");
}

} // namespace
