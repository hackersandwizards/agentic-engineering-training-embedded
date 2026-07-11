#!/bin/sh
set -eu

cd "$(dirname "$0")/.."
mkdir -p .agent-events
payload=$(cat)
printf '%s\n' "$payload" >>.agent-events/stop.jsonl
