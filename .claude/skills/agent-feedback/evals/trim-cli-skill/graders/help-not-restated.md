---
# S24 (SKILL.md:114-116): the CLI's --help is the second owner; lines restating it go
type: regex
target: { source: file, path: agent-config/skills/pkgctl/SKILL.md }
match: not_contains
---
Registry URL to publish to|Print what would be published|Dist tag to attach|One-time password
