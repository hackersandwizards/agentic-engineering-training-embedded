---
# T4 (SKILL.md:19): the final review runs at effort high
type: regex
pattern: '## Step: final review[^\n]*(?:(?!\n## )[\s\S])*?\n[ \t*_-]*Effort:[ \t]*`?high\b'
flags: i
target: { source: file, path: plan/runbook.md }
match: contains
weight: 1
---
