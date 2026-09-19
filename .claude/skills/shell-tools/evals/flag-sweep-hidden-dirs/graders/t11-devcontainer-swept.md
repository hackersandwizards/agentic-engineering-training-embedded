---
# T11 (SKILL.md:28): the flag is gone from the script under .devcontainer/, which a default rg or fd sweep skips
type: regex
pattern: '--legacy-auth'
target: { source: file, path: .devcontainer/post-create.sh }
match: not_contains
weight: 2
---
