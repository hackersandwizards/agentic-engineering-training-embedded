---
# C9 (correction.md:43-44), C7 (correction.md:35): the content of one write belongs to the skill that performs it, so the changelog invariant lands in the release skill
type: regex
target: { source: file, path: agent-config/skills/release/SKILL.md }
match: contains
flags: i
---
customer|client|ticket
