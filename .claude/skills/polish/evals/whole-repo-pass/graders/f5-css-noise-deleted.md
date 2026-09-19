---
# F5 (failure-modes.md:21-22): the sweep covers /* */ comments
type: regex
pattern: '/\* colors \*/|/\* layout \*/'
target: { source: file, path: docs/style.css }
match: not_contains
weight: 0.5
---
