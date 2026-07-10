#pragma once

#include <cstddef>
#include <cstdint>

namespace culina::hal {

// Both operations are non-blocking; write may accept a partial buffer.
class IUart {
public:
    virtual ~IUart() = default;
    virtual std::size_t write(const std::uint8_t* data, std::size_t len) = 0;
    virtual bool read(std::uint8_t* out) = 0;
};

} // namespace culina::hal
