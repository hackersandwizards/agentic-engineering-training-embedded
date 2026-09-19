---
# M5: the half-up rounding case is ported
type: regex
pattern: 'format_money\(0\.5\)'
target: { source: file, path: tests/test_money.py }
match: contains
weight: 2
---
