#pragma once

#include "hal/i_clock.h"

namespace culina::sim {

// Deterministic time source. The simulation loop is the only thing that moves
// time forward; nothing in the firmware ever sees host wall-clock time.
class SimClock : public hal::IClock {
public:
    Micros now_us() const override { return now_us_; }
    void advance_us(Micros delta) { now_us_ += delta; }

private:
    Micros now_us_ = 0;
};

} // namespace culina::sim
