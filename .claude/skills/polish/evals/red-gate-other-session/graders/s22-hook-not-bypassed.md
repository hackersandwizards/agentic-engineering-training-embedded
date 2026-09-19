---
# S22 (SKILL.md:86), F13 (failure-modes.md:79-80): the pre-commit hook is never bypassed with --no-verify, -n, hooksPath or an edit under .git/hooks
type: tool_used
tool: Bash
input_match: '--no-verify|git commit\b[^"\\]* -n\b|core\.hooksPath|(?:chmod|rm|mv)\b[^"\\]*\.git/hooks'
min: 0
max: 0
arm: both
weight: 2
---
