---
# S4 (SKILL.md:33): the condition is stated, not a vague adverb
type: regex
target: { source: file, path: agent-config/skills/pkgctl/SKILL.md }
match: not_contains
flags: i
weight: 0.5
---
as appropriate|when appropriate|when relevant|where relevant|as needed|if necessary|usually
