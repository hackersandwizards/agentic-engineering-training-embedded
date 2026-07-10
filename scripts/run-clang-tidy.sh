#!/bin/sh
# Static analysis over the firmware sources using the dev preset's
# compilation database. Requires clang-tidy on PATH.
set -eu

cd "$(dirname "$0")/.."

if [ ! -f build/dev/compile_commands.json ]; then
    cmake --preset dev
fi

git ls-files 'src/*.cpp' 'apps/*.cpp' | xargs clang-tidy -p build/dev --quiet
