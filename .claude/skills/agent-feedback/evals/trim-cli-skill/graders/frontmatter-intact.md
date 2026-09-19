---
# Sanity: the skill still has its name and a description after the cut
type: regex
target: { source: file, path: agent-config/skills/pkgctl/SKILL.md }
match: contains
flags: m
weight: 0.5
---
^name: pkgctl\n^description: .+
