#pragma once

#include "hal/i_lid.h"
#include "hal/i_scale.h"
#include "mcu/heater_pid.h"
#include "mcu/interlocks.h"
#include "mcu/motor_controller.h"
#include "protocol/link.h"

namespace culina::mcu {

class CommandHandler {
public:
    CommandHandler(c1link::Link* link, MotorController* motor, HeaterPid* pid,
                   Interlocks* interlocks, hal::IScale* scale, hal::ILid* lid)
        : link_(link), motor_(motor), pid_(pid), interlocks_(interlocks), scale_(scale), lid_(lid) {
    }

    void handle(const c1link::Frame& request, const Interlocks::Inputs& state, bool faulted);

    // Returns tare-adjusted grams.
    Grams current_grams();

private:
    using Handler = void (CommandHandler::*)(const c1link::Frame&, const Interlocks::Inputs&);
    struct Entry {
        c1link::MsgId msg_id;
        Handler handler;
    };
    static const Entry kHandlers[];

    void handle_ping(const c1link::Frame& request, const Interlocks::Inputs& state);
    void handle_get_version(const c1link::Frame& request, const Interlocks::Inputs& state);
    void handle_motor_set_target(const c1link::Frame& request, const Interlocks::Inputs& state);
    void handle_motor_stop(const c1link::Frame& request, const Interlocks::Inputs& state);
    void handle_heater_set_target(const c1link::Frame& request, const Interlocks::Inputs& state);
    void handle_heater_off(const c1link::Frame& request, const Interlocks::Inputs& state);
    void handle_scale_tare(const c1link::Frame& request, const Interlocks::Inputs& state);
    void handle_scale_read(const c1link::Frame& request, const Interlocks::Inputs& state);
    void handle_lid_lock(const c1link::Frame& request, const Interlocks::Inputs& state);
    void handle_lid_unlock(const c1link::Frame& request, const Interlocks::Inputs& state);

    void respond(const c1link::Frame& request, const std::uint8_t* payload,
                 std::uint16_t payload_len);
    void nack(const c1link::Frame& request);

    c1link::Link* link_;
    MotorController* motor_;
    HeaterPid* pid_;
    Interlocks* interlocks_;
    hal::IScale* scale_;
    hal::ILid* lid_;
    std::int32_t tare_offset_counts_ = 0;
};

} // namespace culina::mcu
