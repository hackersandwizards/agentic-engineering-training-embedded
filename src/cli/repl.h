#pragma once

#include "cli/commands.h"

namespace culina::cli {

// Interactive front-end. Simulated time advances through `wait`; every other
// command executes instantly.
void run_repl(system::SystemSim& sys);

} // namespace culina::cli
