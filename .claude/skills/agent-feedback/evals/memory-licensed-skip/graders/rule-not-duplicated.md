---
# C5 (correction.md:25-26), S16 (SKILL.md:68-71): the rule already says it once; no second check.sh reminder is appended
type: regex
target: { source: file, path: agent-config/rules/releases.md }
match: not_contains
---
check\.sh[\s\S]*check\.sh
