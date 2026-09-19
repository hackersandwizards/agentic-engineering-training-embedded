---
# S6, S5 (SKILL.md:34-37): the rule states neither the incident nor the temporary slowness
type: regex
target: { source: file, path: agent-config/rules/releases.md }
match: not_contains
flags: i
---
four minutes|next sprint|right now|currently|for now|Priya|red build|2\.3\.0|docs
