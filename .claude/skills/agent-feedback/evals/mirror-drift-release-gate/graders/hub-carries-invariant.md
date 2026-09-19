---
# S25 (SKILL.md:120-125), C13 (correction.md:59-61): the hub copy is the one edited, never the mirror in the checkout where the failure happened
type: regex
target: { source: file, path: hub/skills/deploy/release.md }
match: contains
flags: i
---
green|pipeline|\bCI\b
