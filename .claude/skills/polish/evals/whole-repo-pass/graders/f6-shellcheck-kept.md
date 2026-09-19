---
# F6 (failure-modes.md:23-24): the shellcheck directive in export.sh survives
type: regex
pattern: 'shellcheck disable=SC2086'
target: { source: file, path: scripts/export.sh }
match: contains
weight: 0.5
---
