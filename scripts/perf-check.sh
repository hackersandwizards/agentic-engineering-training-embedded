#!/bin/sh
set -eu

cd "$(dirname "$0")/.."

cmake --preset release -DCULINA_WARNINGS_AS_ERRORS=ON >/dev/null
cmake --build --preset release --target perf_check >/dev/null
./build/release/tests/perf_check
