# Culina C-100 Firmware

Firmware for the Culina C-100 smart kitchen machine: an application processor
(recipes, cooking programs, UI) and a safety/motor MCU (interlocks, motor and
heater control) talking over the C1-Link serial protocol. The entire device —
motor, heater, scale, lid, thermal behaviour — is simulated on the host, so
everything builds and runs anywhere with CMake and a C++17 compiler. It serves
as a realistic playground for agentic engineering exercises.

## Contents

- [Tech Stack](#tech-stack)
- [Architecture](#architecture)
- [Quick Start](#quick-start)
- [Commands & Targets](#commands--targets)
- [Developer Tooling](#developer-tooling)
- [Testing](#testing)
- [Project Structure](#project-structure)
- [C1-Link Protocol](#c1-link-protocol)
- [Simulation & Scenarios](#simulation--scenarios)
- [Contributing](#contributing)
- [License](#license)

## Tech Stack

- **C++17**, no exceptions/RTTI in firmware code (`common`, `protocol`, `mcu`)
- **CMake ≥ 3.24 + Ninja**, presets for dev/tsan/release
- **GoogleTest** via FetchContent (first configure downloads it)
- **clang-format / clang-tidy / .editorconfig** for a uniform codebase
- **ASan+UBSan** in the default `dev` preset, **TSan** in its own preset

## Architecture

```
 ┌───────────────────────────┐         ┌────────────────────────────┐
 │  application processor    │ C1-Link │  safety / motor MCU        │
 │  (culina_app_lib)         │◄───────►│  (culina_mcu_lib)          │
 │  recipes, programs, CLI,  │  UART   │  1 ms tick: interlocks,    │
 │  telemetry store, OTA     │         │  motor ramps, heater PI,   │
 │  10 ms tick               │         │  100 Hz telemetry          │
 └────────────┬──────────────┘         └─────────────┬──────────────┘
              │ hal interfaces (clock, motor, heater, temp, scale, lid)
 ┌────────────┴────────────────────────────────────────┴─────────────┐
 │  simulated board (culina_simulation): thermal plant, motor model, │
 │  scale with vibration noise, lid, deterministic clock             │
 └───────────────────────────────────────────────────────────────────┘
```

The split mirrors the physical device: the MCU alone enforces the safety
requirements (see `docs/safety-requirements.md`); the application processor
is just another untrusted client on the wire.

## Quick Start

```sh
cmake --preset dev
cmake --build --preset dev
./build/dev/apps/culina_sim
```

Then try:

```
add water 500
set-temp 100
wait 5m
status
```

Simulated time only advances through `wait`, so nothing depends on how fast
your machine is.

## Commands & Targets

| Action              | Command                                        | just      |
| ------------------- | ---------------------------------------------- | --------- |
| Configure           | `cmake --preset dev`                           | `just configure` |
| Build               | `cmake --build --preset dev`                   | `just build` |
| All tests           | `ctest --preset dev`                           | `just test` |
| Only unit tests     | `ctest --preset dev -L unit`                   | `just test dev -L unit` |
| Run the simulator   | `./build/dev/apps/culina_sim`                  | `just run` |
| Run a scenario      | `./build/dev/apps/culina_sim --script <file>`  |           |
| Format              | `clang-format -i` over `src tests apps`        | `just fmt` |
| Static analysis     | `scripts/run-clang-tidy.sh`                    | `just tidy` |
| Control-loop timing | `scripts/perf-check.sh`                        | `just perf` |

The `justfile` is a thin optional wrapper; every recipe is a one-liner over
cmake/ctest.

## Developer Tooling

- **Presets:** `dev` (Debug + ASan/UBSan) is the everyday preset. Use `tsan`
  when chasing threading issues and `release` for timing measurements —
  sanitizer overhead distorts them.
- **Warnings:** `-Wall -Wextra -Wconversion` and friends everywhere; turn on
  `-DCULINA_WARNINGS_AS_ERRORS=ON` for gate builds.
- **Offline builds:** pass `-DFETCHCONTENT_SOURCE_DIR_GOOGLETEST=<path>` if
  the first configure cannot reach the network.

## Testing

Three layers, selectable via ctest labels:

- `unit` — pure logic against headers and small fixtures.
- `integration` — both firmwares against the simulated board in one process.
- `scenario` — every `data/scenarios/checks/*.scn` file runs as its own test;
  `expect` lines are the assertions.

The harness is set up; project-specific specs are added as features evolve.
`scripts/perf-check.sh` reports control-loop timing for a long cook.

## Project Structure

```
apps/            culina_sim (single-process), culina_app + culina_mcu (two-process)
cmake/           warnings, sanitizers, GoogleTest fetch
data/recipes/    .rcp recipe files loaded at startup
data/scenarios/  demo/ scripts and checks/ used by the scenario tests
docs/            C1-Link spec, safety requirements, datasheet extracts
src/common/      ring buffer, CRC16, Result, logging, units
src/hal/         hardware interfaces (pure virtual)
src/sim/         simulated board: thermal, motor, scale, lid, transports
src/protocol/    C1-Link framing, parser, link layer
src/mcu/         safety MCU firmware: interlocks, motor, heater PI, telemetry
src/app/         application firmware: MCU client, telemetry store, cooking
                 programs, guided recipes, OTA verification
src/system/      SystemSim: the whole device in one process
src/cli/         REPL, command grammar, scenario runner
tests/           unit/, integration/, support fixtures
```

## C1-Link Protocol

Full specification in [docs/c1link-protocol.md](docs/c1link-protocol.md).
Frame summary:

```
0     2   sync 0xA5 0x5A
2     1   version | flags
3     1   type (1 req, 2 rsp, 3 telemetry, 4 nack)
4     1   sequence
5     1   message id
6     2   payload length (LE, max 250)
8     N   payload (LE fields)
8+N   2   CRC16-CCITT over bytes 2..8+N-1 (LE)
```

Telemetry streams at 100 Hz: tick, temperature (deci-°C), RPM, grams, flags.

## Simulation & Scenarios

The scenario grammar is identical in the REPL and in `.scn` files:

```
add water 500        # put mass in the bowl (water/oil/flour set viscosity)
set-temp 100         # heater target in °C (0 = off)
set-speed 3          # dial 0-10
manual 80 2 15       # temp / dial / minutes as one program
dough 4              # interval kneading for 4 minutes
sous-vide 63.5 45    # hold 63.5 °C for 45 minutes
turbo 1500           # locked-lid pulse, milliseconds
load Bread Dough     # start a guided recipe, advance with `next`
lid open|close|lock|unlock
tare / weigh / status
ota-verify 512       # verify a 512 KiB staged image
wait 5m              # advance simulated time
expect temp >= 99    # assertion (scripts); also: rpm, weight, avg-temp, state, lid
```

Two-process mode, with the C1-Link on a real socket:

```sh
./build/dev/apps/culina_mcu --water 500     # terminal 1
./build/dev/apps/culina_app                 # terminal 2
```

Killing either side leaves the other running — useful for poking at link
behaviour with real process lifecycles.

## Contributing

Branch from `main`, run format, tidy, and the test suite before a PR:

```sh
just fmt && just tidy && just test
```

## License

For training purposes. See [LICENSE](LICENSE).
