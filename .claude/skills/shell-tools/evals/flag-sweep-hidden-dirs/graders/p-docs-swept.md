---
# P (prompt): the flag is gone from the visible docs/deploy.md
type: regex
pattern: '--legacy-auth'
target: { source: file, path: docs/deploy.md }
match: not_contains
weight: 0.5
---
