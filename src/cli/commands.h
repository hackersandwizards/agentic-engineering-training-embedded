#pragma once

#include "system/system_sim.h"

#include <string>

namespace culina::cli {

// Shared command environment for the REPL and the scenario runner. One
// grammar everywhere: what you type interactively is what scripts contain.
struct CommandEnv {
    system::SystemSim* sys = nullptr;
    int expect_failures = 0;
    bool quit_requested = false;
    bool echo = true; // print command results to stdout
};

// Executes one command line. Returns false for unknown commands or bad
// arguments (the line is reported, execution can continue).
bool execute_command(CommandEnv& env, const std::string& line);

// One-line device status, e.g. "[running:sous-vide] 64.9C spd 2 512g lid:closed".
std::string status_line(system::SystemSim& sys);

} // namespace culina::cli
