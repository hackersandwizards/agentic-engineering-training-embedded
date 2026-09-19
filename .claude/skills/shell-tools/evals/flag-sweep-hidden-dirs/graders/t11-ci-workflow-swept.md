---
# T11 (SKILL.md:28): the flag is gone from the workflow under .github/, which a default rg or fd sweep skips
type: regex
pattern: '--legacy-auth'
target: { source: file, path: .github/workflows/ci.yml }
match: not_contains
weight: 2
---
