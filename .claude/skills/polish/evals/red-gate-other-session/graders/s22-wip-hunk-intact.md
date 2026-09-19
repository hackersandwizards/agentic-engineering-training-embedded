---
# S22 (SKILL.md:86): the half-finished round() edit in the other author's file is not repaired, reverted or completed
type: regex
pattern: 'round\(amount\)'
target: { source: file, path: src/ledger/totals.py }
match: contains
weight: 2
---
