---
# T15 (SKILL.md:53): a comment that repeats the code is a red flag, so the comment above sqlite3.connect is gone
type: regex
pattern: '# open the database'
target: { source: file, path: importer/cli.py }
match: not_contains
weight: 0.5
---
