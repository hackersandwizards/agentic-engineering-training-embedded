---
# F5 (failure-modes.md:21-22): the sweep covers # comments in shell, so the noise in export.sh is gone
type: regex
pattern: '# input and output paths|# print the output path'
target: { source: file, path: scripts/export.sh }
match: not_contains
---
