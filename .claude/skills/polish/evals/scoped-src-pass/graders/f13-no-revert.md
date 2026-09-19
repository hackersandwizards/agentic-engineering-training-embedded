---
# F13 (failure-modes.md:78-80), S10 (SKILL.md:38): no checkout, restore or clean, which destroy the other author's unstaged work or leave the branch noted in phase 1
type: tool_used
tool: Bash
input_match: 'git (checkout|restore|clean)\b'
min: 0
max: 0
arm: both
---
