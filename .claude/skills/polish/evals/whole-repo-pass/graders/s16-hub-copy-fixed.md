---
# S16 (SKILL.md:65-68), S14 (SKILL.md:56-58): the dead pointer scripts/check.sh is fixed in the canonical copy under agent-config/, never only in the mirror the sync overwrites
type: regex
pattern: 'scripts/check\.sh'
target: { source: file, path: agent-config/skills/release/SKILL.md }
match: not_contains
weight: 2
---
