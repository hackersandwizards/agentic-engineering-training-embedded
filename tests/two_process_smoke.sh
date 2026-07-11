#!/bin/sh
set -eu

if [ "$#" -ne 2 ]; then
    echo "usage: $0 CULINA_MCU CULINA_APP" >&2
    exit 2
fi

tmp=$(mktemp -d "${TMPDIR:-/tmp}/culina-two-process.XXXXXX")
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

wait_for_count() {
    pattern=$1
    expected=$2
    attempts=0
    while [ "$attempts" -lt 100 ]; do
        count=$(grep -Ec -- "$pattern" "$app_log" || true)
        [ "$count" -ge "$expected" ] && return 0
        kill -0 "$app_pid" 2>/dev/null || return 1
        attempts=$((attempts + 1))
        sleep 0.05
    done
    return 1
}

wait_for_safe_status() {
    attempts=0
    while [ "$attempts" -lt 100 ]; do
        echo "status" >&3
        grep -Eq 'flags 0x01$' "$app_log" && return 0
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
wait_for_count '^culina-app: connected' 1 || fail_with_logs

echo "set-temp nan" >&3
wait_for_count '^-> invalid-argument$' 1 || fail_with_logs
echo "set-speed 99" >&3
wait_for_count '^-> invalid-argument$' 2 || fail_with_logs

echo "set-temp 65" >&3
wait_for_count '^-> Ok$' 1 || fail_with_logs
wait_for_count '^-> complete$' 1 || fail_with_logs
echo "set-speed 2" >&3
wait_for_count '^-> Ok$' 2 || fail_with_logs
wait_for_count '^-> complete$' 2 || fail_with_logs

echo "stop" >&3
wait_for_count '^-> stop complete$' 1 || fail_with_logs
wait_for_safe_status || fail_with_logs
echo "quit" >&3
exec 3>&-

status=0
wait "$app_pid" || status=$?
app_pid=
[ "$status" -eq 0 ] || fail_with_logs
