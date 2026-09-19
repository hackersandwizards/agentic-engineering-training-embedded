---
# F4 (failure-modes.md:19-20): the one comment stating what the code cannot (bank exports repeat the last row of a page) survives
type: regex
pattern: '(?:repeat|duplicat)\w* the last row|last row of (?:each|every|a) page'
target: { source: file, path: src/ledger/parse.py }
match: contains
weight: 0.5
---
