---
# S23 (SKILL.md:90-92): the sweep of parse.py is committed by pathspec, so the commit log names it
type: regex
pattern: 'src/ledger/parse\.py'
target: { source: file, path: .eval/commits.log }
match: contains
---
