---
# T3 (SKILL.md:18): everyday coding, the json flag, runs at effort low
type: regex
pattern: '## Step: json flag[^\n]*(?:(?!\n## )[\s\S])*?\n[ \t*_-]*Effort:[ \t]*`?low\b'
flags: i
target: { source: file, path: plan/runbook.md }
match: contains
weight: 1
---
