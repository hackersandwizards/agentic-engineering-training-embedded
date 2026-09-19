---
# S3 (SKILL.md:20-21): the copy in the other author's uncommitted file stays whatever it says, reported as deferred
type: regex
pattern: 'integer cents'
target: { source: file, path: src/ledger/totals.py }
match: contains
weight: 2
---
