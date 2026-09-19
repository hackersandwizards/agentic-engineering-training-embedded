---
# S6 (SKILL.md:36-37): an artifact states a rule or a measurement, never a status
type: regex
target: { source: file, path: agent-config/skills/pkgctl/SKILL.md }
match: not_contains
flags: i
---
currently|migrating|until that lands|redirect warning
