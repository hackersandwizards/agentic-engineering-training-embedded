#include "cli/script_runner.h"

#include <cstdio>
#include <fstream>
#include <string>

namespace culina::cli {

Status run_script(system::SystemSim& sys, const char* path, bool echo) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::fprintf(stderr, "cannot open scenario: %s\n", path);
        return Status::InvalidArgument;
    }

    CommandEnv env;
    env.sys = &sys;
    env.echo = echo;

    std::string line;
    int line_number = 0;
    bool parse_error = false;
    while (std::getline(file, line)) {
        ++line_number;
        if (!execute_command(env, line)) {
            std::fprintf(stderr, "%s:%d: bad command: %s\n", path, line_number, line.c_str());
            parse_error = true;
        }
        if (env.quit_requested) {
            break;
        }
    }

    if (parse_error) {
        return Status::InvalidArgument;
    }
    return env.expect_failures == 0 ? Status::Ok : Status::ProtocolError;
}

} // namespace culina::cli
