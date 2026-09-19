---
# S7 (SKILL.md:31): the other author's modified file is not edited, so its committed noise comment is still there
type: regex
pattern: '# create the dict'
target: { source: file, path: src/ledger/totals.py }
match: contains
weight: 2
---
