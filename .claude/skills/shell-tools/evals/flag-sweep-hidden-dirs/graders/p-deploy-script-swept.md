---
# P (prompt): the flag is gone from the visible scripts/deploy.sh
type: regex
pattern: '--legacy-auth'
target: { source: file, path: scripts/deploy.sh }
match: not_contains
weight: 0.5
---
