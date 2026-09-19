---
# S5 (SKILL.md:34-35): version changes and prior incidents go; the rule keeps only what makes it enforceable
type: regex
target: { source: file, path: agent-config/skills/pkgctl/SKILL.md }
match: not_contains
flags: i
---
v0\.9|wrong registry|before that|three publishes
