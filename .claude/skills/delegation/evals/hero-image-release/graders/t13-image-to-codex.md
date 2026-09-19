---
# T13 (SKILL.md:45-46): the hero image, the one capability Claude lacks, is the step whose executor is a codex command
type: regex
pattern: '## Step:[^\n]*(hero|image)[^\n]*(?:(?!\n## )[\s\S])*?\n[ \t*_-]*Executor:[^\n]*\bcodex\b'
flags: i
target: { source: file, path: plan/delegation.md }
match: contains
weight: 1
---
