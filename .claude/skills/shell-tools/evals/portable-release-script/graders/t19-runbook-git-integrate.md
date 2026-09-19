---
# T19 (SKILL.md:43): the runbook merges the release branch with the git integrate alias
type: regex
pattern: '\bgit\s+integrate\s'
target: { source: file, path: RELEASE.md }
match: contains
weight: 1
---
