---
# M5: the negative-amount format_money case from the deleted file lives on in tests/test_money.py
type: regex
pattern: '-1,234\.56'
target: { source: file, path: tests/test_money.py }
match: contains
weight: 2
---
