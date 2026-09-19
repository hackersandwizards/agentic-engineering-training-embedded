---
# T5 (SKILL.md:20): the eval run, a fixed fixture where volume sets the cost, runs on luna
type: regex
pattern: '## Step: eval run[^\n]*(?:(?!\n## )[\s\S])*?\n[ \t*_-]*Model:[^\n]*luna'
flags: i
target: { source: file, path: plan/runbook.md }
match: contains
weight: 2
---
