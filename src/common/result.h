#pragma once

#include <cstdint>

namespace culina {

// Firmware builds disable exceptions.
enum class Status : std::uint8_t {
    Ok = 0,
    Timeout,
    CrcMismatch,
    Overflow,
    InvalidArgument,
    NotReady,
    HardwareFault,
    ProtocolError,
};

const char* status_name(Status status);

template <typename T>
class Result {
public:
    static Result ok(T value) {
        Result r;
        r.status_ = Status::Ok;
        r.value_ = value;
        return r;
    }

    static Result err(Status status) {
        Result r;
        r.status_ = status;
        return r;
    }

    bool is_ok() const { return status_ == Status::Ok; }
    Status status() const { return status_; }
    const T& value() const { return value_; }

private:
    Result() = default;
    Status status_ = Status::Ok;
    T value_{};
};

} // namespace culina
