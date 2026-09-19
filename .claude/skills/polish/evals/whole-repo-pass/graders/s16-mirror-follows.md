---
# S16 (SKILL.md:67-68): the mirror under .claude/ carries the fix too, through the sync or by hand
type: regex
pattern: 'scripts/check\.sh'
target: { source: file, path: .claude/skills/release/SKILL.md }
match: not_contains
weight: 0.5
---
