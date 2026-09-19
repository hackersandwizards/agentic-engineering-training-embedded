---
# T8 (SKILL.md:27-35): the client mail is authored by claude -p, in the command or in the brief Codex receives
type: regex
pattern: '## Step: client mail[^\n]*(?:(?!\n## )[\s\S])*?claude -p'
flags: i
target: { source: file, path: plan/runbook.md }
match: contains
weight: 2
---
