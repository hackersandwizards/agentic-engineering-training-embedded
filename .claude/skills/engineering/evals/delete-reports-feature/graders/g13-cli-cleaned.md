---
# G13: the cli no longer imports or dispatches the report command
type: regex
pattern: 'report'
target: { source: file, path: shop/cli.py }
match: not_contains
---
