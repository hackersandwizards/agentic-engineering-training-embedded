---
# T11 (SKILL.md:28): the flag is gone from the dotfile .acmectl.env, which a default rg or fd sweep skips
type: regex
pattern: '--legacy-auth'
target: { source: file, path: .acmectl.env }
match: not_contains
weight: 2
---
