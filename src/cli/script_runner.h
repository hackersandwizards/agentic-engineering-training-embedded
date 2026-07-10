#pragma once

#include "cli/commands.h"

namespace culina::cli {

// Executes a .scn scenario file against a SystemSim. Returns Status::Ok when
// every line parsed and every expect held.
Status run_script(system::SystemSim& sys, const char* path, bool echo = true);

} // namespace culina::cli
