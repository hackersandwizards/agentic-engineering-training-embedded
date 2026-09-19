---
# T10 (SKILL.md:26-27): the regenerated report holds the Berlin buckets, 3 6 4 6 1, with June 5 present
type: regex
pattern: '2026-06-01\t3\n2026-06-02\t6\n2026-06-03\t4\n2026-06-04\t6\n2026-06-05\t1'
target: { source: file, path: reports/daily.tsv }
match: contains
weight: 3
---
