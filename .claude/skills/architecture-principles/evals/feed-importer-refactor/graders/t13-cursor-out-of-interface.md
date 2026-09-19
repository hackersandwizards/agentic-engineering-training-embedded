---
# T13 (SKILL.md:53-54): implementation contaminating the interface is a red flag, so the CLI no longer creates the cursor the writer needs and hands it down
type: regex
pattern: 'cursor\s*=|\.cursor\('
target: { source: file, path: importer/cli.py }
match: not_contains
weight: 2
---
