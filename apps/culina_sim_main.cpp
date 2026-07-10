#include "cli/repl.h"
#include "cli/script_runner.h"
#include "common/logging.h"

#include <cstring>

int main(int argc, char** argv) {
    const char* script = nullptr;
    const char* recipe_dir = "data/recipes";
    std::uint32_t seed = 42;

    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "--script") == 0 && i + 1 < argc) {
            script = argv[++i];
        } else if (std::strcmp(argv[i], "--recipes") == 0 && i + 1 < argc) {
            recipe_dir = argv[++i];
        } else if (std::strcmp(argv[i], "--seed") == 0 && i + 1 < argc) {
            seed = static_cast<std::uint32_t>(std::strtoul(argv[++i], nullptr, 10));
        } else {
            std::fprintf(stderr, "usage: %s [--script file.scn] [--recipes dir] [--seed n]\n",
                         argv[0]);
            return 2;
        }
    }

    culina::system::SystemSim sim(seed);
    if (sim.recipes().load_directory(recipe_dir) != culina::Status::Ok) {
        CULINA_LOG_WARN("no recipe directory at %s", recipe_dir);
    }

    if (script != nullptr) {
        return culina::cli::run_script(sim, script) == culina::Status::Ok ? 0 : 1;
    }

    culina::cli::run_repl(sim);
    return 0;
}
