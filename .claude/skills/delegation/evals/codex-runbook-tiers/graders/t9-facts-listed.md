---
# T9 (SKILL.md:35): the mail brief names the subject line, the language and the signature among the facts
type: regex
pattern: '## Step: client mail[^\n]*(?=(?:(?!\n## )[\s\S])*?\bsubject\b)(?=(?:(?!\n## )[\s\S])*?\bsignature\b)(?=(?:(?!\n## )[\s\S])*?\b(language|German|Deutsch)\b)'
flags: i
target: { source: file, path: plan/runbook.md }
match: contains
weight: 0.5
---
