---
# F6 (failure-modes.md:23-24): the noqa directive survives the sweep
type: regex
pattern: 'noqa: E731'
target: { source: file, path: src/ledger/parse.py }
match: contains
weight: 0.5
---
