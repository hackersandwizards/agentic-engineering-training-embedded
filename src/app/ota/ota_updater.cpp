#include "app/ota/ota_updater.h"

#include "common/crc16.h"
#include "common/logging.h"

namespace culina::app {

Status OtaUpdater::begin(const std::uint8_t* image, std::size_t len,
                         std::uint16_t expected_crc) {
    if (image == nullptr || len == 0) {
        return Status::InvalidArgument;
    }
    if (state_ == State::Verifying) {
        return Status::NotReady;
    }
    image_ = image;
    image_len_ = len;
    verified_ = 0;
    expected_crc_ = expected_crc;
    running_crc_ = 0xFFFF;
    state_ = State::Verifying;
    CULINA_LOG_INFO("ota: verifying %zu byte image", len);
    return Status::Ok;
}

void OtaUpdater::step() {
    if (state_ != State::Verifying) {
        return;
    }
    std::size_t chunk = image_len_ - verified_;
    if (chunk > kChunkBytes) {
        chunk = kChunkBytes;
    }
    running_crc_ = crc16_ccitt(image_ + verified_, chunk, running_crc_);
    verified_ += chunk;

    if (verified_ >= image_len_) {
        state_ = running_crc_ == expected_crc_ ? State::Ready : State::Failed;
        CULINA_LOG_INFO("ota: verification %s",
                        state_ == State::Ready ? "succeeded" : "FAILED");
    }
}

unsigned OtaUpdater::progress_percent() const {
    if (image_len_ == 0) {
        return 0;
    }
    return static_cast<unsigned>(verified_ * 100 / image_len_);
}

} // namespace culina::app
