#!/bin/sh
set -eu

cd "$(dirname "$0")/.."

if ! command -v clang-tidy >/dev/null 2>&1; then
    echo "clang-tidy is required but was not found on PATH" >&2
    exit 1
fi

if [ ! -f build/dev/compile_commands.json ]; then
    cmake --preset dev -DCULINA_WARNINGS_AS_ERRORS=ON
fi

if [ "$(uname -s)" = "Darwin" ]; then
    sdk=$(xcrun --show-sdk-path)
    git ls-files 'src/*.cpp' 'apps/*.cpp' 'tools/*.cpp' |
        while IFS= read -r file; do
            clang-tidy -p build/dev --quiet --warnings-as-errors='*' \
                --extra-arg=-isysroot --extra-arg="$sdk" "$file"
        done
else
    git ls-files 'src/*.cpp' 'apps/*.cpp' 'tools/*.cpp' |
        xargs -n 1 clang-tidy -p build/dev --quiet --warnings-as-errors='*'
fi
