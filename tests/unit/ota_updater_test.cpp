#include "app/ota/ota_updater.h"

#include "common/crc16.h"

#include <gtest/gtest.h>

#include <vector>

namespace {

using culina::Status;
using culina::app::OtaUpdater;

std::vector<std::uint8_t> fake_image(std::size_t len) {
    std::vector<std::uint8_t> image(len);
    for (std::size_t i = 0; i < len; ++i) {
        image[i] = static_cast<std::uint8_t>(i * 31 + 7);
    }
    return image;
}

TEST(OtaUpdater, VerifiesAGoodImageInChunks) {
    const auto image = fake_image(3 * OtaUpdater::kChunkBytes + 100);
    const std::uint16_t crc = culina::crc16_ccitt(image.data(), image.size());

    OtaUpdater ota;
    ASSERT_EQ(ota.begin(image.data(), image.size(), crc), Status::Ok);
    EXPECT_TRUE(ota.busy());

    int steps = 0;
    while (ota.busy()) {
        ota.step();
        ++steps;
    }
    EXPECT_EQ(steps, 4);
    EXPECT_EQ(ota.state(), OtaUpdater::State::Ready);
    EXPECT_EQ(ota.progress_percent(), 100u);
}

TEST(OtaUpdater, RejectsACorruptImage) {
    auto image = fake_image(OtaUpdater::kChunkBytes);
    const std::uint16_t crc = culina::crc16_ccitt(image.data(), image.size());
    image[100] ^= 0xFF;

    OtaUpdater ota;
    ASSERT_EQ(ota.begin(image.data(), image.size(), crc), Status::Ok);
    while (ota.busy()) {
        ota.step();
    }
    EXPECT_EQ(ota.state(), OtaUpdater::State::Failed);
}

TEST(OtaUpdater, RefusesEmptyImageAndDoubleStart) {
    OtaUpdater ota;
    EXPECT_EQ(ota.begin(nullptr, 0, 0), Status::InvalidArgument);

    const auto image = fake_image(2 * OtaUpdater::kChunkBytes);
    ASSERT_EQ(ota.begin(image.data(), image.size(), 0), Status::Ok);
    EXPECT_EQ(ota.begin(image.data(), image.size(), 0), Status::NotReady);
}

} // namespace
