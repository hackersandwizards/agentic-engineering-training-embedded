#!/bin/sh
set -eu

if [ "$#" -ne 2 ]; then
    echo "usage: $0 CULINA_MCU CULINA_APP" >&2
    exit 2
fi

tmp=$(mktemp -d "${TMPDIR:-/tmp}/culina-disconnect.XXXXXX")
socket="$tmp/c1link.sock"
input="$tmp/input"
mcu_log="$tmp/mcu.log"
app_log="$tmp/app.log"
mcu_pid=
app_pid=

cleanup() {
    [ -z "$app_pid" ] || kill "$app_pid" 2>/dev/null || true
    [ -z "$mcu_pid" ] || kill "$mcu_pid" 2>/dev/null || true
    [ -z "$app_pid" ] || wait "$app_pid" 2>/dev/null || true
    [ -z "$mcu_pid" ] || wait "$mcu_pid" 2>/dev/null || true
    rm -rf "$tmp"
}
trap cleanup EXIT HUP INT TERM

wait_for_socket() {
    attempts=0
    while [ "$attempts" -lt 100 ]; do
        [ -S "$socket" ] && return 0
        kill -0 "$mcu_pid" 2>/dev/null || return 1
        attempts=$((attempts + 1))
        sleep 0.05
    done
    return 1
}

wait_for_line() {
    pattern=$1
    attempts=0
    while [ "$attempts" -lt 100 ]; do
        grep -Eq -- "$pattern" "$app_log" && return 0
        kill -0 "$app_pid" 2>/dev/null || return 1
        attempts=$((attempts + 1))
        sleep 0.05
    done
    return 1
}

fail_with_logs() {
    cat "$app_log" >&2
    cat "$mcu_log" >&2
    exit 1
}

mkfifo "$input"
"$1" --socket "$socket" --water 500 >"$mcu_log" 2>&1 &
mcu_pid=$!
wait_for_socket || fail_with_logs

"$2" --socket "$socket" <"$input" >"$app_log" 2>&1 &
app_pid=$!
exec 3>"$input"
wait_for_line '^culina-app: connected' || fail_with_logs
echo "set-temp 65" >&3
wait_for_line '^-> Ok$' || fail_with_logs
wait_for_line '^-> complete$' || fail_with_logs
kill "$mcu_pid"
wait "$mcu_pid" 2>/dev/null || true
mcu_pid=

status=0
wait "$app_pid" || status=$?
app_pid=
exec 3>&-

if [ "$status" -eq 0 ] || ! grep -q -- 'MCU link disconnected' "$app_log"; then
    fail_with_logs
fi
