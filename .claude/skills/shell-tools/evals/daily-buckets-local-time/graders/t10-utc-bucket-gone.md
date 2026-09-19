---
# T10 (SKILL.md:26-27): the UTC bucket of five events on June 1 is gone from the report
type: regex
pattern: '2026-06-01\t5'
target: { source: file, path: reports/daily.tsv }
match: not_contains
weight: 1
---
