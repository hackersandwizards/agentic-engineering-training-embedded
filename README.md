# Culina C-100 firmware

Culina is a fictional smart kitchen machine built as an embedded engineering
training system. It combines application firmware, safety MCU firmware, a
binary serial protocol, hardware abstractions and a deterministic host
simulation. The repository is a complete, working reference implementation,
not production firmware for a real appliance.

The supported development platforms are macOS and Linux. The first CMake
configure downloads GoogleTest and therefore needs an internet connection.

## Quick start

Install Git, CMake 3.24 or newer, Ninja, a GCC or Clang C++17 compiler,
`clang-format`, `clang-tidy` and ShellCheck. This is the completed reference;
participants begin from the separate one-commit baseline. Then run:

```sh
./scripts/verify-setup.sh
./build/dev/apps/culina_sim
```

At the simulator prompt:

```text
add water 500
set-temp 100
wait 5m
status
```

Simulated time advances only through `wait`, so scenarios remain deterministic
and do not depend on host speed.

## Touchscreen simulator

An optional Qt Quick interface runs the application processor and safety MCU as
separate host processes. On macOS, install Qt and launch both with one command:

```sh
brew install qt
just ui
```

Mouse clicks and trackpad gestures act as touchscreen input. The panel beside
the Culina display represents physical actions such as adding ingredients or
opening the lid; those actions travel over a simulation-only control socket,
not the device's C1-Link protocol. Qt is optional and the normal build and test
presets remain unchanged.

## Architecture

```text
application firmware       C1-Link        safety MCU firmware
recipes, programs, CLI  <------------>   interlocks, motor, heater
10 ms tick                   UART         1 ms tick, 100 Hz telemetry
          \                                  /
           +------ hardware interfaces -----+
                          |
                 deterministic simulator
```

The MCU enforces the safety requirements independently. The application
processor is treated as an untrusted protocol client. See
[the safety requirements](docs/safety-requirements.md) and
[the C1-Link specification](docs/c1link-protocol.md).

## Common commands

| Action | Command | Optional `just` wrapper |
| --- | --- | --- |
| Configure | `cmake --preset dev` | `just configure` |
| Build | `cmake --build --preset dev` | `just build` |
| Run all tests | `ctest --preset dev` | `just test` |
| Run unit tests | `ctest --preset dev -L unit` | `just test dev -L unit` |
| Run simulator | `./build/dev/apps/culina_sim` | `just run` |
| Run touchscreen | `./scripts/run-ui.sh` | `just ui` |
| Format sources | `clang-format -i ...` | `just fmt` |
| Static analysis | `./scripts/run-clang-tidy.sh` | `just tidy` |
| Measure loop timing | `./scripts/perf-check.sh` | `just perf` |
| Run the local quality gate | `./scripts/gate.sh` | `just gate` |

The `dev` preset enables AddressSanitizer and UndefinedBehaviorSanitizer. The
`tsan` preset enables ThreadSanitizer. The `release` preset is used for timing
measurements because sanitizer overhead would distort the result.

## Tests

CTest labels expose four layers:

- `unit` tests pure logic and small components.
- `integration` runs both firmware sides against the simulated board.
- `scenario` executes the checked-in `.scn` acceptance scenarios.
- `tool` verifies host-side protocol tooling with valid and malformed data.

The quality gate configures a warnings-as-errors build, compiles all targets,
runs every test, performs static analysis and checks the release timing budget.

## Project structure

```text
apps/            simulator and two-process host applications
.claude/         example skills, custom agents and observable hook configuration
.claude-plugin/  local marketplace for the packaged training example
cmake/           compiler warnings, sanitizers and dependencies
data/recipes/    guided recipe inputs
data/scenarios/  demonstrations and executable acceptance checks
docs/            protocol, safety requirements and component data
exercises/       generic two-day participant exercises
src/app/         application firmware
src/cli/         command parser and scenario runner
src/common/      shared fixed-size and protocol utilities
src/hal/         hardware interfaces
src/mcu/         safety MCU firmware
src/protocol/    C1-Link framing and transport
src/sim/         deterministic hardware models and transports
src/system/      complete single-process system simulation
tests/           unit, integration, scenario, tool and performance checks
tools/           host-side protocol diagnostics
plugins/         shareable agent artifact example
```

## Agentic Engineering reference artifacts

The completed repository includes two custom skills, two focused read-only
reviewers, an observable stop hook and a marketplace plugin. They are reference
outcomes, not participant starting material. The two-day path in `exercises/`
builds equivalent artifacts only after participants observe a reason for each.

No MCP server is enabled in the reference repository. MCP configuration depends
on the external system, credentials and task selected during the exercise; a
checked-in placeholder would be a non-working integration.

## C1-Link summary

```text
offset  size  field
0       2     sync 0xA5 0x5A
2       1     version and flags
3       1     frame type
4       1     sequence
5       1     message ID
6       2     payload length, little-endian, maximum 250
8       N     payload, little-endian fields
8+N     2     CRC16-CCITT over version through payload
```

Telemetry streams at 100 Hz and contains the tick, bowl temperature, motor
speed, weight and status flags. Application requests receive a correlated
response or NACK. Active outputs enter a safe state if valid application
traffic stops for five seconds.

## Simulator commands

The interactive prompt and `.scn` files use the same grammar:

```text
add water 500
set-temp 100
set-speed 3
manual 80 2 15
dough 4
sous-vide 63.5 45
turbo 1500
load Bread Dough
lid open|close|lock|unlock
tare
weigh
status
ota-verify 512
wait 5m
expect temp >= 99
```

Two-process mode carries C1-Link over a Unix domain socket:

```sh
./build/dev/apps/culina_mcu --water 500
./build/dev/apps/culina_app
```

Stopping one side leaves the other running, which makes link supervision and
recovery observable under real process lifecycles.

## Contributing

This training repository follows trunk-based development. Keep changes small,
work from an up-to-date `main` and run `just gate` before pushing.

## License

For training purposes. See [LICENSE](LICENSE).
