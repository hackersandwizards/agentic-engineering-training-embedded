---
# S23 (SKILL.md:90-92): the src/ edits are committed by pathspec, so the commit log names parse.py
type: regex
pattern: 'src/ledger/parse\.py'
target: { source: file, path: .eval/commits.log }
match: contains
---
