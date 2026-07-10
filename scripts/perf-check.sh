#!/bin/sh
# Control-loop timing for a long cook. Run before and after a change to see
# the difference; uses the release preset because sanitizer overhead
# distorts timing.
set -eu

cd "$(dirname "$0")/.."

cmake --preset release >/dev/null
cmake --build --preset release --target perf_check >/dev/null
./build/release/tests/perf_check
