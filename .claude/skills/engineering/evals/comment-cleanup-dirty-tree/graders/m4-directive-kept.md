---
# M4: the noqa directive survives
type: regex
pattern: 'noqa: E731'
target: { source: file, path: ledger/parse.py }
match: contains
---
