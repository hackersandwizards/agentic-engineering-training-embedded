---
# S26 (SKILL.md:127-130): a mirror that is not a declared fork and carries edits the hub lacks is copied to the hub first, or the sync deletes those lines everywhere
type: regex
target: { source: file, path: hub/skills/deploy/release.md }
match: contains
flags: i
---
changelog
