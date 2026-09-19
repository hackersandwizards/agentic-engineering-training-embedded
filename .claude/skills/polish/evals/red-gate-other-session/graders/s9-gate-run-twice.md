---
# S9 (SKILL.md:36), S20 (SKILL.md:82): the gate runs at preflight for the baseline and again in verify, so at least twice
type: tool_used
tool: Bash
input_match: '(?:"command"\s*:\s*"|[;&]\s*|\\n\s*)(?:\./|bash |sh )check\.sh'
min: 2
arm: both
weight: 0.5
---
