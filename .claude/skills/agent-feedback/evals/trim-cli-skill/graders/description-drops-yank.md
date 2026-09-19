---
# S14 (SKILL.md:58-61): a cut is not finished until the frontmatter description matches it; yank leaves the description and the body together
type: regex
target: { source: file, path: agent-config/skills/pkgctl/SKILL.md }
match: not_contains
flags: i
---
yank
