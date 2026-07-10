#include "mcu/command_handler.h"

namespace culina::mcu {

using namespace c1link;

namespace {
constexpr float kCountsPerGram = 10.0f;
}

const CommandHandler::Entry CommandHandler::kHandlers[] = {
    {MsgId::Ping, &CommandHandler::handle_ping},
    {MsgId::GetVersion, &CommandHandler::handle_get_version},
    {MsgId::MotorSetTarget, &CommandHandler::handle_motor_set_target},
    {MsgId::MotorStop, &CommandHandler::handle_motor_stop},
    {MsgId::HeaterSetTarget, &CommandHandler::handle_heater_set_target},
    {MsgId::HeaterOff, &CommandHandler::handle_heater_off},
    {MsgId::ScaleTare, &CommandHandler::handle_scale_tare},
    {MsgId::ScaleRead, &CommandHandler::handle_scale_read},
    {MsgId::LidLock, &CommandHandler::handle_lid_lock},
    {MsgId::LidUnlock, &CommandHandler::handle_lid_unlock},
};

void CommandHandler::respond(const Frame& request, const std::uint8_t* payload,
                             std::uint16_t payload_len) {
    link_->send(FrameType::Response, request.seq, request.msg_id, payload, payload_len);
}

void CommandHandler::nack(const Frame& request) {
    link_->send(FrameType::Nack, request.seq, request.msg_id, nullptr, 0);
}

Grams CommandHandler::current_grams() {
    const auto raw = scale_->read_raw();
    if (!raw.is_ok()) {
        return 0;
    }
    return static_cast<Grams>(static_cast<float>(raw.value() - tare_offset_counts_) /
                              kCountsPerGram);
}

void CommandHandler::handle(const Frame& request, const Interlocks::Inputs& state) {
    if (request.type != FrameType::Request) {
        return;
    }
    for (const Entry& entry : kHandlers) {
        if (entry.msg_id == request.msg_id) {
            (this->*entry.handler)(request, state);
            return;
        }
    }
    nack(request);
}

void CommandHandler::handle_ping(const Frame& request, const Interlocks::Inputs&) {
    respond(request, nullptr, 0);
}

void CommandHandler::handle_get_version(const Frame& request, const Interlocks::Inputs&) {
    const std::uint8_t version[] = {0, 9, 0};
    respond(request, version, sizeof(version));
}

void CommandHandler::handle_motor_set_target(const Frame& request,
                                             const Interlocks::Inputs& state) {
    if (request.payload_len != 3) {
        nack(request);
        return;
    }
    const Rpm requested = get_u16(request.payload);
    const std::uint8_t ramp = request.payload[2];
    if (ramp == kRampBurst) {
        // Burst runs are only allowed with the lid locked.
        if (!state.lid_locked) {
            nack(request);
            return;
        }
        motor_->burst(requested);
        respond(request, nullptr, 0);
        return;
    }
    const Rpm allowed = interlocks_->clamp_speed_request(requested, state);
    motor_->set_target(allowed, ramp);
    std::uint8_t granted[2];
    put_u16(granted, allowed);
    respond(request, granted, sizeof(granted));
}

void CommandHandler::handle_motor_stop(const Frame& request, const Interlocks::Inputs&) {
    motor_->stop();
    respond(request, nullptr, 0);
}

void CommandHandler::handle_heater_set_target(const Frame& request, const Interlocks::Inputs&) {
    if (request.payload_len != 2) {
        nack(request);
        return;
    }
    const DeciCelsius target = get_i16(request.payload);
    if (target < 370 || target > 1600) { // user range 37.0-160.0 C
        nack(request);
        return;
    }
    pid_->set_target(target);
    respond(request, nullptr, 0);
}

void CommandHandler::handle_heater_off(const Frame& request, const Interlocks::Inputs&) {
    pid_->disable();
    respond(request, nullptr, 0);
}

void CommandHandler::handle_scale_tare(const Frame& request, const Interlocks::Inputs&) {
    const auto raw = scale_->read_raw();
    if (!raw.is_ok()) {
        nack(request);
        return;
    }
    tare_offset_counts_ = raw.value();
    respond(request, nullptr, 0);
}

void CommandHandler::handle_scale_read(const Frame& request, const Interlocks::Inputs&) {
    std::uint8_t grams[4];
    put_i32(grams, current_grams());
    respond(request, grams, sizeof(grams));
}

void CommandHandler::handle_lid_lock(const Frame& request, const Interlocks::Inputs&) {
    lid_->set_lock(true);
    std::uint8_t locked = lid_->is_locked() ? 1 : 0;
    respond(request, &locked, 1);
}

void CommandHandler::handle_lid_unlock(const Frame& request, const Interlocks::Inputs&) {
    lid_->set_lock(false);
    respond(request, nullptr, 0);
}

} // namespace culina::mcu
