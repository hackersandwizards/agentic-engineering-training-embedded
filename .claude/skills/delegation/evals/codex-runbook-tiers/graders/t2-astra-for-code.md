---
# T2 (SKILL.md:14): the everyday coding step runs on the repository default, gpt-6-astra
type: regex
pattern: '## Step: json flag[^\n]*(?:(?!\n## )[\s\S])*?\n[ \t*_-]*Model:[^\n]*astra'
flags: i
target: { source: file, path: plan/runbook.md }
match: contains
weight: 0.5
---
