---
# T12 (SKILL.md:40-41), P: out/mail.txt still holds both errors; the text was not changed in this session
type: regex
pattern: 'Wednesday[\s\S]*kickoff/4171'
target: { source: file, path: out/mail.txt }
match: contains
weight: 1
---
