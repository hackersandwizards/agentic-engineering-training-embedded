#include "cli/repl.h"

#include <cstdio>
#include <string>

namespace culina::cli {

void run_repl(system::SystemSim& sys) {
    std::printf("Culina C-100 simulator. Type 'help' for commands, 'quit' to exit.\n");
    std::printf("Time advances with 'wait <duration>', e.g. 'wait 5m'.\n\n");

    // Give the device a moment to boot and stream first telemetry.
    sys.step_ms(50);

    CommandEnv env;
    env.sys = &sys;

    char buffer[256];
    while (!env.quit_requested) {
        std::printf("%s\n", status_line(sys).c_str());
        std::printf("culina> ");
        std::fflush(stdout);
        if (std::fgets(buffer, sizeof(buffer), stdin) == nullptr) {
            break;
        }
        execute_command(env, std::string(buffer));
    }
}

} // namespace culina::cli
