# Convenience wrapper; every recipe is a one-liner over cmake/ctest.

default: build

configure preset="dev":
    cmake --preset {{ preset }}

build preset="dev":
    cmake --build --preset {{ preset }}

test preset="dev" *args="":
    ctest --preset {{ preset }} {{ args }}

run *args="":
    cmake --build --preset dev --target culina_sim
    ./build/dev/apps/culina_sim {{ args }}

fmt:
    git ls-files '*.h' '*.cpp' | xargs clang-format -i

tidy:
    ./scripts/run-clang-tidy.sh

perf:
    ./scripts/perf-check.sh
