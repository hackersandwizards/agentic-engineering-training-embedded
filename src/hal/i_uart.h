#pragma once

#include <cstddef>
#include <cstdint>

namespace culina::hal {

// Byte-stream link between the two processors. Non-blocking on both sides:
// write() returns how many bytes were accepted, read() returns false when no
// byte is pending.
class IUart {
public:
    virtual ~IUart() = default;
    virtual std::size_t write(const std::uint8_t* data, std::size_t len) = 0;
    virtual bool read(std::uint8_t* out) = 0;
};

} // namespace culina::hal
