---
# G13: the cli test for the report command is gone
type: regex
pattern: 'test_report|"report"'
target: { source: file, path: tests/test_cli.py }
match: not_contains
---
