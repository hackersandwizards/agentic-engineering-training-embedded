---
# S19 (SKILL.md:82-84): the reference itself is cut, by name and by description
type: regex
target: { source: file, path: agent-config/skills/pkgctl/SKILL.md }
match: not_contains
flags: i
---
versioning\.md|versioning rule|the rule (on|for|about) versioning
