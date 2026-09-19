---
# F5 (failure-modes.md:21-22): the banner block labelling the section below it is gone
type: regex
pattern: '-{4,} helpers -{4,}'
target: { source: file, path: src/ledger/parse.py }
match: not_contains
weight: 0.5
---
