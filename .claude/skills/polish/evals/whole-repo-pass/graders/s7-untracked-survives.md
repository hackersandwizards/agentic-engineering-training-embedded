---
# S7 (SKILL.md:31): the other author's untracked file keeps its own noise comment, so it was not swept
type: regex
pattern: '# loop over the rows'
target: { source: file, path: src/ledger/weekly.py }
match: contains
---
