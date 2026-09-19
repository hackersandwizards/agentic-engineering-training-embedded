---
# S3 (SKILL.md:18-20): the false fact (amounts as integer cents) is fixed in README.md although the argument named src/
type: regex
pattern: 'integer cents'
target: { source: file, path: README.md }
match: not_contains
weight: 2
---
