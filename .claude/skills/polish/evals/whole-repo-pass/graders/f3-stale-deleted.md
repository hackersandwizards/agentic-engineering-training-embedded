---
# F3 (failure-modes.md:16-18): the stale comment (the code returns a float, not cents) is gone
type: regex
pattern: 'integers in cents'
target: { source: file, path: src/ledger/parse.py }
match: not_contains
weight: 0.5
---
