#pragma once

#include "common/result.h"

#include <cstddef>
#include <cstdint>

namespace culina::app {

// Verifies a staged firmware image before it is handed to the bootloader.
// Verification is chunked across ticks so the UI can show progress.
class OtaUpdater {
public:
    enum class State { Idle, Verifying, Ready, Failed };

    Status begin(const std::uint8_t* image, std::size_t len, std::uint16_t expected_crc);
    void step();

    State state() const { return state_; }
    bool busy() const { return state_ == State::Verifying; }
    unsigned progress_percent() const;

    static constexpr std::size_t kChunkBytes = 4096;

private:
    State state_ = State::Idle;
    const std::uint8_t* image_ = nullptr;
    std::size_t image_len_ = 0;
    std::size_t verified_ = 0;
    std::uint16_t expected_crc_ = 0;
    std::uint16_t running_crc_ = 0xFFFF;
};

} // namespace culina::app
