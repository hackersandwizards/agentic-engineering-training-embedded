#pragma once

namespace culina::sim {

// Lid with an electromagnetic lock. Opening is refused while locked, matching
// the mechanical latch on the real machine.
class LidModel {
public:
    bool is_closed() const { return closed_; }
    bool is_locked() const { return locked_; }

    void user_open() {
        if (!locked_) {
            closed_ = false;
        }
    }
    void user_close() { closed_ = true; }

    void set_lock(bool locked) {
        if (closed_) {
            locked_ = locked;
        }
    }

private:
    bool closed_ = true;
    bool locked_ = false;
};

} // namespace culina::sim
