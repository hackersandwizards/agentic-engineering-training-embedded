---
# T3 (SKILL.md:18): the README typo, everyday work, runs at effort low rather than a tier below it
type: regex
pattern: '## Step: readme typo[^\n]*(?:(?!\n## )[\s\S])*?\n[ \t*_-]*Effort:[ \t]*`?low\b'
flags: i
target: { source: file, path: plan/runbook.md }
match: contains
weight: 0.5
---
