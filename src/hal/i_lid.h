#pragma once

namespace culina::hal {

// Lid position switch and electromagnetic lock.
class ILid {
public:
    virtual ~ILid() = default;
    virtual bool is_closed() const = 0;
    virtual bool is_locked() const = 0;
    virtual void set_lock(bool locked) = 0;
};

} // namespace culina::hal
