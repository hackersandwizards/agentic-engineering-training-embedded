#pragma once

#include "app/mcu_client.h"
#include "app/telemetry_store.h"
#include "common/time_types.h"

namespace culina::app {

struct ProgramContext {
    McuClient* mcu = nullptr;
    TelemetryStore* telemetry = nullptr;
    Millis elapsed_ms = 0;
};

// A cooking program drives the device through McuClient, one 10 ms tick at a
// time. Commands can be refused while another is in flight, so programs
// re-issue until accepted.
class Program {
public:
    virtual ~Program() = default;
    virtual const char* name() const = 0;
    virtual void on_tick(ProgramContext& ctx) = 0;
    virtual bool finished(const ProgramContext& ctx) const = 0;
    virtual void on_stop(ProgramContext& ctx) = 0;

    // One line of user-facing state for the display.
    virtual const char* status(const ProgramContext& ctx) const = 0;
};

constexpr Rpm dial_to_rpm(std::uint8_t dial) {
    return static_cast<Rpm>((dial > 10 ? 10 : dial) * 1070);
}

} // namespace culina::app
