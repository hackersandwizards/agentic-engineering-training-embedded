---
# S3 (SKILL.md:18-19): the docstring under src/ no longer claims integer cents
type: regex
pattern: 'integer cents'
target: { source: file, path: src/ledger/parse.py }
match: not_contains
---
