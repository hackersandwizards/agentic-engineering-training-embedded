---
# S19 (SKILL.md:82-87): an always-on rule is already in the reader's context, so its citation goes and is not paraphrased into the skill
type: regex
target: { source: file, path: agent-config/skills/pkgctl/SKILL.md }
match: not_contains
flags: i
---
commits\.md|paths named|name the paths|its paths|pathspec|git add -A
