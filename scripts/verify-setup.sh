#!/bin/sh
# Checks that this machine can build and run the firmware: configure, build,
# unit tests, one scenario. Prints SETUP OK at the end.
set -eu

cd "$(dirname "$0")/.."

echo "== configure (dev preset)"
cmake --preset dev >/dev/null

echo "== build"
cmake --build --preset dev >/dev/null

echo "== unit tests"
ctest --preset dev -L unit --output-on-failure >/dev/null

echo "== scenario smoke test"
./build/dev/apps/culina_sim --script data/scenarios/checks/turbo_cold.scn >/dev/null

echo "SETUP OK"
