---
# S25, S27 (SKILL.md:122-125, 135-136): the change reaches the checkout through the sync, so a mirror edited directly and then overwritten fails here
type: regex
target: { source: file, path: repos/alpha/.claude/skills/deploy/release.md }
match: contains
flags: i
---
green|pipeline|\bCI\b
