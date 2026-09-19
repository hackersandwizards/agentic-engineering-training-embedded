---
# T14 (SKILL.md:33): the runbook fetches the previous checksum with xh, not curl
type: regex
pattern: '(?:^|[\s`$(|])xh\s'
flags: m
target: { source: file, path: RELEASE.md }
match: contains
weight: 1
---
