---
# T4 (SKILL.md:19): the race, a hard bug, runs at effort high
type: regex
pattern: '## Step: race fix[^\n]*(?:(?!\n## )[\s\S])*?\n[ \t*_-]*Effort:[ \t]*`?high\b'
flags: i
target: { source: file, path: plan/runbook.md }
match: contains
weight: 1
---
