---
# S19 (SKILL.md:86-87): a paths-scoped rule loads only after the skill has fired, so its clause is inlined
type: regex
target: { source: file, path: agent-config/skills/pkgctl/SKILL.md }
match: contains
flags: i
---
\bmajor\b
