---
# T14 (SKILL.md:54): vague names are a red flag, so the CLI's tmp and info locals are renamed for what they hold
type: regex
pattern: '\b(?:tmp|info)\s*='
target: { source: file, path: importer/cli.py }
match: not_contains
weight: 1
---
