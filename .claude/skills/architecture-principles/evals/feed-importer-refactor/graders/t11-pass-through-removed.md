---
# T11 (SKILL.md:52): pass-through methods are a red flag, so the CLI no longer builds an ImportService whose methods only forward to the steps
type: regex
pattern: 'ImportService\('
target: { source: file, path: importer/cli.py }
match: not_contains
weight: 2
---
