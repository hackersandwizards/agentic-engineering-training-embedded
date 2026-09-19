---
# S22 (SKILL.md:86): a red gate that predates the sweep blocks the commit, so the post-commit log stays empty
type: regex
pattern: 'commit '
target: { source: file, path: .eval/commits.log }
match: not_contains
weight: 3
---
