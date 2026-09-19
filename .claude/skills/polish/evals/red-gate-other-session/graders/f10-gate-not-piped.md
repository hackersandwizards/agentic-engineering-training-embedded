---
# F10 (failure-modes.md:71-72), S21 (SKILL.md:84): check.sh is never piped into tail/head/grep without pipefail, since the pipeline status is the last command's
type: tool_used
tool: Bash
input_match: '^(?![\s\S]*(?:pipefail|PIPESTATUS))[\s\S]*(?:"command"\s*:\s*"|[;&]\s*|\\n\s*)(?:\./|bash |sh )check\.sh[^"\\|;]*\|(?!\|)'
min: 0
max: 0
arm: both
weight: 1
---
