---
# T12 (SKILL.md:29): the runbook views the CHANGELOG diff through delta
type: regex
pattern: '\bdelta\b'
target: { source: file, path: RELEASE.md }
match: contains
weight: 1
---
