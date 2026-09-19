---
# S26 (SKILL.md:130-131): a declared fork drifting from the hub is the fork working; its line is never lifted into the hub
type: regex
target: { source: file, path: hub/skills/deploy/release.md }
match: not_contains
flags: i
---
ops channel|ops acknowledgement
