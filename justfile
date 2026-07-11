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

ui:
    ./scripts/run-ui.sh

fmt:
    git ls-files -z '*.h' '*.cpp' | xargs -0 clang-format -i

format-check:
    git ls-files -z '*.h' '*.cpp' | xargs -0 clang-format --dry-run --Werror

tidy:
    ./scripts/run-clang-tidy.sh

perf:
    ./scripts/perf-check.sh

gate:
    ./scripts/gate.sh
