---
# S16 (SKILL.md:67-68): the sync script is run after the hub edit, and its output read
type: tool_used
tool: Bash
input_match: '(?:"command"\s*:\s*"|[;&]\s*|\\n\s*)(?:\./|bash |sh )?scripts/sync-agent-config\.sh'
min: 1
arm: both
weight: 0.5
---
