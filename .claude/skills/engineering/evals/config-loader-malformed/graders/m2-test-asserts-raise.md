---
# M2, G9: the new test asserts that malformed input raises
type: regex
pattern: 'assertRaises|raises\('
target: { source: file, path: tests/test_config.py }
match: contains
---
