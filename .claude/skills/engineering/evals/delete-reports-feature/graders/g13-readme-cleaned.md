---
# G13: the README no longer documents the report command
type: regex
pattern: 'report'
target: { source: file, path: README.md }
match: not_contains
weight: 0.5
---
