---
# S11 (SKILL.md:50-52): the invariant goes in the job file where it fires, never in the router
type: regex
target: { source: file, path: hub/skills/deploy/SKILL.md }
match: not_contains
flags: i
---
green|pipeline|\bCI\b
