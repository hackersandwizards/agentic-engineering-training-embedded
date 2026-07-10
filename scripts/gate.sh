#!/bin/sh
set -eu

cd "$(dirname "$0")/.."

for tool in cmake ninja clang-format clang-tidy shellcheck; do
    if ! command -v "$tool" >/dev/null 2>&1; then
        echo "Missing gate dependency: $tool" >&2
        exit 1
    fi
done

echo "Checking shell scripts"
shellcheck scripts/*.sh tests/*.sh

echo "Checking source formatting"
git ls-files -z '*.h' '*.cpp' |
    xargs -0 clang-format --dry-run --Werror

echo "Building with sanitizers and warnings as errors"
cmake --preset dev -DCULINA_WARNINGS_AS_ERRORS=ON >/dev/null
cmake --build --preset dev >/dev/null

echo "Running all tests"
ctest --preset dev --output-on-failure

echo "Running static analysis"
./scripts/run-clang-tidy.sh

echo "Checking the release timing budget"
./scripts/perf-check.sh

echo "QUALITY GATE PASSED"
