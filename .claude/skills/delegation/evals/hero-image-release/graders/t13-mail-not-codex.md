---
# T13 (SKILL.md:45-46): no codex step is briefed to author the announcement mail; Codex is never started to author text
type: regex
pattern: '\n[ \t*_-]*Executor:[^\n]*\bcodex\b(?:(?!\n## )[\s\S])*?(?<!not |never |no |not to |never to )\b(write|draft|compose|author)\b[^\n]{0,60}\b(mail|e-?mail|announcement|newsletter)\b'
flags: i
target: { source: file, path: plan/delegation.md }
match: not_contains
weight: 2
---
