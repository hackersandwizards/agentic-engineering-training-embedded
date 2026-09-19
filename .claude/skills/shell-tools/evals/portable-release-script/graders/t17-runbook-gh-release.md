---
# T17 (SKILL.md:38): the runbook publishes the release through gh release
type: regex
pattern: '\bgh\s+release\s+(?:create|upload)\b'
target: { source: file, path: RELEASE.md }
match: contains
weight: 0.5
---
