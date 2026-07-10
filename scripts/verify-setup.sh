#!/bin/sh
set -eu

cd "$(dirname "$0")/.."

for tool in git cmake ninja c++ clang-format clang-tidy shellcheck; do
    if ! command -v "$tool" >/dev/null 2>&1; then
        echo "Missing required tool: $tool" >&2
        exit 1
    fi
done

echo "Configuring the sanitizer build"
cmake --preset dev -DCULINA_WARNINGS_AS_ERRORS=ON >/dev/null

echo "Building all targets"
cmake --build --preset dev >/dev/null

echo "Running the setup smoke tests"
ctest --preset dev -L 'unit|scenario|tool' --output-on-failure >/dev/null

echo "SETUP OK"
