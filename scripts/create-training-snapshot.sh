#!/bin/sh
set -eu

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 OUTPUT_DIRECTORY" >&2
    exit 2
fi

root=$(CDPATH='' cd -- "$(dirname "$0")/.." && pwd -P)

if ! git -C "$root" diff --quiet || ! git -C "$root" diff --cached --quiet ||
    [ -n "$(git -C "$root" ls-files --others --exclude-standard)" ]; then
    echo "Commit or remove all tracked and untracked changes before creating a snapshot" >&2
    exit 1
fi

requested_output=$1
case "$requested_output" in
    /*) ;;
    *) requested_output="$(pwd)/$requested_output" ;;
esac

case "$requested_output/" in
    "$root/"*)
        echo "Output must be outside the source repository" >&2
        exit 1
        ;;
esac

output_parent=$(dirname "$requested_output")
output_name=$(basename "$requested_output")
mkdir -p "$output_parent"
output_parent=$(CDPATH='' cd -- "$output_parent" && pwd -P)
output="$output_parent/$output_name"

case "$output/" in
    "$root/"*)
        echo "Output must be outside the source repository" >&2
        exit 1
        ;;
esac

if [ -e "$output" ]; then
    echo "Output already exists: $output" >&2
    exit 1
fi

cleanup() {
    status=$?
    trap - EXIT HUP INT TERM
    if [ "$status" -ne 0 ] && [ -n "${output:-}" ] && [ -e "$output" ]; then
        rm -rf -- "${output:?}"
    fi
    exit "$status"
}
trap cleanup EXIT HUP INT TERM

mkdir "$output"
git -C "$root" archive --format=tar HEAD | tar -xf - -C "$output"
git -C "$output" init -q -b main
git -C "$output" add -A
git -C "$output" \
    -c user.name="Training Setup" \
    -c user.email="training@hackersandwizards.de" \
    commit -q -m "Start training"

count=$(git -C "$output" rev-list --count HEAD)
remotes=$(git -C "$output" remote)
if [ "$count" -ne 1 ] || [ -n "$remotes" ] ||
    [ "$(git -C "$output" branch --show-current)" != "main" ]; then
    echo "Snapshot verification failed" >&2
    exit 1
fi

trap - EXIT HUP INT TERM
echo "Created one-commit snapshot from $(git -C "$root" rev-parse --short HEAD) at $output"
