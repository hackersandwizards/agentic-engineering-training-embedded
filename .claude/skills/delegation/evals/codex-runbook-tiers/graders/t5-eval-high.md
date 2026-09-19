---
# T5 (SKILL.md:20): the eval run's effort is high
type: regex
pattern: '## Step: eval run[^\n]*(?:(?!\n## )[\s\S])*?\n[ \t*_-]*Effort:[ \t]*`?high\b'
flags: i
target: { source: file, path: plan/runbook.md }
match: contains
weight: 1
---
