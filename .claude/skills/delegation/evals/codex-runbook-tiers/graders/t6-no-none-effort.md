---
# T6 (SKILL.md:22): no codex step names an effort Astra does not accept, none or minimal
type: regex
pattern: '\n[ \t*_-]*Command:[^\n]*\bcodex\b(?:(?!\n## )[\s\S])*?\n[ \t*_-]*Effort:[ \t]*`?(none|minimal)\b'
flags: i
target: { source: file, path: plan/runbook.md }
match: not_contains
weight: 1
---
