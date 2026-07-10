#include "cli/commands.h"

#include "app/cooking/dough_mode.h"
#include "app/cooking/sous_vide_mode.h"
#include "app/cooking/steam_mode.h"
#include "app/cooking/turbo_pulse.h"
#include "common/crc16.h"

#include <cstdarg>
#include <cstdio>
#include <memory>
#include <sstream>
#include <vector>

namespace culina::cli {

using app::SessionState;

namespace {

std::vector<std::string> tokenize(const std::string& line) {
    std::istringstream stream(line);
    std::vector<std::string> tokens;
    std::string token;
    while (stream >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// Durations: "500ms", "30s", "5m", or a bare millisecond count.
bool parse_duration_ms(const std::string& text, std::uint32_t* out) {
    try {
        std::size_t suffix = 0;
        const long value = std::stol(text, &suffix);
        if (value < 0) {
            return false;
        }
        const std::string unit = text.substr(suffix);
        if (unit == "ms" || unit.empty()) {
            *out = static_cast<std::uint32_t>(value);
        } else if (unit == "s") {
            *out = static_cast<std::uint32_t>(value) * 1000u;
        } else if (unit == "m") {
            *out = static_cast<std::uint32_t>(value) * 60000u;
        } else {
            return false;
        }
        return true;
    } catch (const std::exception&) {
        return false;
    }
}

void say(const CommandEnv& env, const char* fmt, ...) __attribute__((format(printf, 2, 3)));
void say(const CommandEnv& env, const char* fmt, ...) {
    if (!env.echo) {
        return;
    }
    va_list args;
    va_start(args, fmt);
    std::vprintf(fmt, args);
    va_end(args);
    std::printf("\n");
}

float telemetry_temp_c(system::SystemSim& sys) {
    return to_celsius(sys.store().latest().deci_celsius);
}

bool handle_add(CommandEnv& env, const std::vector<std::string>& args) {
    if (args.size() != 3) {
        return false;
    }
    const float grams = std::stof(args[2]);
    env.sys->board().add_mass(grams);
    if (args[1] == "water") {
        env.sys->board().set_viscosity(1.0f);
    } else if (args[1] == "oil") {
        env.sys->board().set_viscosity(1.8f);
    } else if (args[1] == "flour" || args[1] == "dough") {
        env.sys->board().set_viscosity(6.5f);
    } else {
        env.sys->board().set_viscosity(2.0f);
    }
    say(env, "added %.0f g of %s", static_cast<double>(grams), args[1].c_str());
    return true;
}

bool handle_expect(CommandEnv& env, const std::vector<std::string>& args) {
    if (args.size() != 4) {
        return false;
    }
    const std::string& metric = args[1];
    const std::string& op = args[2];
    const std::string& expected = args[3];

    std::string actual_text;
    float actual = 0.0f;
    bool numeric = true;

    if (metric == "temp") {
        actual = telemetry_temp_c(*env.sys);
    } else if (metric == "avg-temp") {
        actual = env.sys->store().average_temp_c(2000);
    } else if (metric == "rpm") {
        actual = static_cast<float>(env.sys->store().latest().rpm);
    } else if (metric == "weight") {
        actual = static_cast<float>(env.sys->store().latest().grams);
    } else if (metric == "state") {
        numeric = false;
        actual_text = app::session_state_name(env.sys->controller().state());
    } else if (metric == "lid") {
        numeric = false;
        const auto flags = env.sys->store().latest().flags;
        actual_text = (flags & c1link::kFlagLidLocked) != 0   ? "locked"
                      : (flags & c1link::kFlagLidClosed) != 0 ? "closed"
                                                              : "open";
    } else {
        return false;
    }

    bool pass = false;
    if (numeric) {
        const float want = std::stof(expected);
        if (op == ">=") {
            pass = actual >= want;
        } else if (op == "<=") {
            pass = actual <= want;
        } else if (op == ">") {
            pass = actual > want;
        } else if (op == "<") {
            pass = actual < want;
        } else if (op == "==") {
            pass = actual == want;
        } else if (op == "!=") {
            pass = actual != want;
        } else {
            return false;
        }
        if (!pass) {
            std::fprintf(stderr, "EXPECT FAILED: %s %s %s (actual %.2f)\n", metric.c_str(),
                         op.c_str(), expected.c_str(), static_cast<double>(actual));
        }
    } else {
        if (op == "==") {
            pass = actual_text == expected;
        } else if (op == "!=") {
            pass = actual_text != expected;
        } else {
            return false;
        }
        if (!pass) {
            std::fprintf(stderr, "EXPECT FAILED: %s %s %s (actual %s)\n", metric.c_str(),
                         op.c_str(), expected.c_str(), actual_text.c_str());
        }
    }
    if (pass) {
        say(env, "expect %s %s %s: ok", metric.c_str(), op.c_str(), expected.c_str());
    } else {
        ++env.expect_failures;
    }
    return true;
}

bool handle_ota(CommandEnv& env, const std::vector<std::string>& args) {
    static std::vector<std::uint8_t> image;
    std::size_t kib = 512;
    bool corrupt = false;
    if (args.size() >= 2) {
        kib = static_cast<std::size_t>(std::stoul(args[1]));
    }
    if (args.size() >= 3 && args[2] == "corrupt") {
        corrupt = true;
    }
    image.resize(kib * 1024);
    for (std::size_t i = 0; i < image.size(); ++i) {
        image[i] = static_cast<std::uint8_t>(i * 13 + 5);
    }
    const std::uint16_t crc = crc16_ccitt(image.data(), image.size());
    if (corrupt) {
        image[image.size() / 2] ^= 0xFF;
    }
    if (env.sys->ota().begin(image.data(), image.size(), crc) != Status::Ok) {
        say(env, "ota: busy");
        return true;
    }
    say(env, "ota: verifying %zu KiB image", kib);
    return true;
}

} // namespace

std::string status_line(system::SystemSim& sys) {
    const auto sample = sys.store().latest();
    const auto flags = sample.flags;
    const char* lid = (flags & c1link::kFlagLidLocked) != 0   ? "locked"
                      : (flags & c1link::kFlagLidClosed) != 0 ? "closed"
                                                              : "open";
    const Millis t = sys.now_ms();
    char buf[160];
    std::snprintf(buf, sizeof(buf), "[%s:%s %s] %.1fC spd%.0f %ldg lid:%s t=%02u:%02u:%02u",
                  app::session_state_name(sys.controller().state()), sys.controller().program_name(),
                  sys.controller().program_status(), static_cast<double>(to_celsius(sample.deci_celsius)),
                  static_cast<double>(sample.rpm) / 1070.0, static_cast<long>(sample.grams), lid,
                  t / 3600000u, (t / 60000u) % 60u, (t / 1000u) % 60u);
    return buf;
}

bool execute_command(CommandEnv& env, const std::string& line) {
    const auto args = tokenize(line);
    if (args.empty() || args[0][0] == '#') {
        return true;
    }
    system::SystemSim& sys = *env.sys;
    const std::string& cmd = args[0];

    try {
        if (cmd == "help") {
            say(env, "commands: status add set-temp set-speed manual dough steam sous-vide "
                     "turbo load next stop tare weigh lid ota-verify wait expect quit");
        } else if (cmd == "status") {
            say(env, "%s", status_line(sys).c_str());
        } else if (cmd == "add") {
            return handle_add(env, args);
        } else if (cmd == "set-temp" && args.size() == 2) {
            const float celsius = std::stof(args[1]);
            const Status s = celsius <= 0.0f ? sys.client().heater_off()
                                             : sys.client().set_heater(from_celsius(celsius));
            say(env, "set-temp: %s", status_name(s));
        } else if (cmd == "set-speed" && args.size() == 2) {
            const auto dial = static_cast<std::uint8_t>(std::stoul(args[1]));
            const Status s = sys.client().set_motor(app::dial_to_rpm(dial), c1link::kRampNormal);
            say(env, "set-speed: %s", status_name(s));
        } else if (cmd == "manual" && args.size() == 4) {
            const Status s = sys.controller().start_manual(
                from_celsius(std::stof(args[1])), static_cast<std::uint8_t>(std::stoul(args[2])),
                static_cast<std::uint32_t>(std::stoul(args[3])) * 60u);
            say(env, "manual: %s", status_name(s));
        } else if (cmd == "dough" && args.size() == 2) {
            const Status s = sys.controller().start_program(std::make_unique<app::DoughMode>(
                static_cast<std::uint32_t>(std::stoul(args[1])) * 60u));
            say(env, "dough: %s", status_name(s));
        } else if (cmd == "steam" && args.size() == 2) {
            const Status s = sys.controller().start_program(std::make_unique<app::SteamMode>(
                static_cast<std::uint32_t>(std::stoul(args[1])) * 60u));
            say(env, "steam: %s", status_name(s));
        } else if (cmd == "sous-vide" && args.size() == 3) {
            const Status s = sys.controller().start_program(std::make_unique<app::SousVideMode>(
                from_celsius(std::stof(args[1])),
                static_cast<std::uint32_t>(std::stoul(args[2])) * 60u));
            say(env, "sous-vide: %s", status_name(s));
        } else if (cmd == "turbo" && args.size() == 2) {
            const Status s = sys.controller().start_program(std::make_unique<app::TurboPulse>(
                static_cast<std::uint32_t>(std::stoul(args[1]))));
            say(env, "turbo: %s", status_name(s));
        } else if (cmd == "load" && args.size() >= 2) {
            std::string name = args[1];
            for (std::size_t i = 2; i < args.size(); ++i) {
                name += " " + args[i];
            }
            const app::Recipe* recipe = sys.recipes().find(name.c_str());
            if (recipe == nullptr) {
                say(env, "load: no recipe named '%s'", name.c_str());
                return true;
            }
            say(env, "load: %s", status_name(sys.controller().start_recipe(recipe)));
        } else if (cmd == "next") {
            sys.controller().user_next();
            say(env, "next: ok");
        } else if (cmd == "stop") {
            sys.controller().stop();
            say(env, "stop: ok");
        } else if (cmd == "tare") {
            say(env, "tare: %s", status_name(sys.client().tare()));
        } else if (cmd == "weigh") {
            say(env, "weight: %ld g", static_cast<long>(sys.store().latest().grams));
        } else if (cmd == "lid" && args.size() == 2) {
            if (args[1] == "open") {
                sys.board().open_lid();
            } else if (args[1] == "close") {
                sys.board().close_lid();
            } else if (args[1] == "lock") {
                sys.client().lock_lid(true);
            } else if (args[1] == "unlock") {
                sys.client().lock_lid(false);
            } else {
                return false;
            }
            say(env, "lid %s: ok", args[1].c_str());
        } else if (cmd == "ota-verify") {
            return handle_ota(env, args);
        } else if (cmd == "wait" && args.size() == 2) {
            std::uint32_t ms = 0;
            if (!parse_duration_ms(args[1], &ms)) {
                return false;
            }
            sys.step_ms(ms);
        } else if (cmd == "expect") {
            return handle_expect(env, args);
        } else if (cmd == "quit" || cmd == "exit") {
            env.quit_requested = true;
        } else {
            std::fprintf(stderr, "unknown command: %s\n", line.c_str());
            return false;
        }
    } catch (const std::exception& e) {
        std::fprintf(stderr, "bad arguments in '%s': %s\n", line.c_str(), e.what());
        return false;
    }
    return true;
}

} // namespace culina::cli
