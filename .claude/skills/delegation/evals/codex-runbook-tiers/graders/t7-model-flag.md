---
# T7 (SKILL.md:23): the luna pick is a per-invocation override on the eval run's command line
type: regex
pattern: '## Step: eval run[^\n]*(?:(?!\n## )[\s\S])*?\n[ \t*_-]*Command:[^\n]*(--model[ =]|-m |model\s*=)[^\n]*luna'
flags: i
target: { source: file, path: plan/runbook.md }
match: contains
weight: 1
---
