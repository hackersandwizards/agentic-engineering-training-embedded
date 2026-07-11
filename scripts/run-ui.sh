#!/bin/sh
set -eu

cd "$(dirname "$0")/.."

if command -v brew >/dev/null 2>&1 && brew --prefix qt >/dev/null 2>&1; then
    cmake --preset ui -DCMAKE_PREFIX_PATH="$(brew --prefix qt)"
else
    cmake --preset ui
fi
cmake --build --preset ui --target culina_mcu culina_ui

tmp=$(mktemp -d "${TMPDIR:-/tmp}/culina-ui.XXXXXX")
c1_socket="$tmp/c1link.sock"
control_socket="$tmp/control.sock"
mcu_log="$tmp/mcu.log"
mcu_pid=

cleanup() {
    if [ -n "$mcu_pid" ]; then
        kill "$mcu_pid" 2>/dev/null || true
        wait "$mcu_pid" 2>/dev/null || true
    fi
    rm -rf "$tmp"
}
trap cleanup EXIT HUP INT TERM

./build/ui/apps/culina_mcu --socket "$c1_socket" --control-socket "$control_socket" \
    >"$mcu_log" 2>&1 &
mcu_pid=$!

i=0
while [ "$i" -lt 500 ]; do
    if [ -S "$c1_socket" ] && [ -S "$control_socket" ]; then
        break
    fi
    if ! kill -0 "$mcu_pid" 2>/dev/null; then
        sed -n '1,200p' "$mcu_log" >&2
        exit 1
    fi
    i=$((i + 1))
    sleep 0.01
done
if [ ! -S "$c1_socket" ] || [ ! -S "$control_socket" ]; then
    echo "Culina MCU did not create its sockets" >&2
    sed -n '1,200p' "$mcu_log" >&2
    exit 1
fi

ui=./build/ui/apps/culina_ui
if [ -x ./build/ui/apps/culina_ui.app/Contents/MacOS/culina_ui ]; then
    ui=./build/ui/apps/culina_ui.app/Contents/MacOS/culina_ui
fi

"$ui" --socket "$c1_socket" --control-socket "$control_socket" --recipes data/recipes
