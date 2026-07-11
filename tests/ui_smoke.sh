#!/bin/sh
set -eu

tmp=$(mktemp -d "${TMPDIR:-/tmp}/culina-ui-smoke.XXXXXX")
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

"$1" --socket "$c1_socket" --control-socket "$control_socket" >"$mcu_log" 2>&1 &
mcu_pid=$!

i=0
while [ "$i" -lt 500 ]; do
    [ -S "$c1_socket" ] && [ -S "$control_socket" ] && break
    kill -0 "$mcu_pid" 2>/dev/null || exit 1
    i=$((i + 1))
    sleep 0.01
done

QT_QPA_PLATFORM=offscreen "$2" --socket "$c1_socket" --control-socket "$control_socket" \
    --recipes "$3" --smoke-test
