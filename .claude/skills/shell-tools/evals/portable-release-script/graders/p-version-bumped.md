---
# P (prompt): the run wrote 1.3.0 to VERSION
type: regex
pattern: '^1\.3\.0\s*$'
target: { source: file, path: VERSION }
match: contains
weight: 0.5
---
