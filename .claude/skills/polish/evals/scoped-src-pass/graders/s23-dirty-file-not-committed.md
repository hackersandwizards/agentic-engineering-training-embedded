---
# S23 (SKILL.md:90), S7 (SKILL.md:31): no commit carries the other author's file (the post-commit hook logs every committed path)
type: regex
pattern: 'src/ledger/totals\.py|src/ledger/weekly\.py'
target: { source: file, path: .eval/commits.log }
match: not_contains
weight: 2
---
