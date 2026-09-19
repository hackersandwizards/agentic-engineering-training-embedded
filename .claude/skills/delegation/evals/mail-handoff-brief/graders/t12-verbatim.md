---
# T12 (SKILL.md:40-41): the brief says the claude -p output is delivered verbatim
type: regex
pattern: '(?<!\bnot\b[^\n.]{0,25})\b(verbatim|unchanged|byte[- ]for[- ]byte|word[- ]for[- ]word|as[- ]is\b|exactly as (it is|returned|received|produced|output)|without (any )?(change|edit|rewording))'
flags: i
target: { source: file, path: plan/deliver.md }
match: contains
weight: 1
---
