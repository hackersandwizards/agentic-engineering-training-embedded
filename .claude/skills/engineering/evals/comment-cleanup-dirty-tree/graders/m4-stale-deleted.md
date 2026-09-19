---
# M4: the stale comment (the code returns a float, not cents) is gone
type: regex
pattern: 'integers in cents'
target: { source: file, path: ledger/parse.py }
match: not_contains
---
