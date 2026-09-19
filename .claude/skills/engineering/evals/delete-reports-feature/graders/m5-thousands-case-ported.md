---
# M5: the thousands-separator case is ported
type: regex
pattern: '1,000,000\.00'
target: { source: file, path: tests/test_money.py }
match: contains
weight: 2
---
