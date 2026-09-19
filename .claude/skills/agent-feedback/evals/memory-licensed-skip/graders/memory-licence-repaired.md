---
# C11 (correction.md:51-52): the memory line that licensed the skip is repaired, not countered by a reminder
type: regex
target: { source: file, path: .claude/agent-memory/releaser/MEMORY.md }
match: not_contains
flags: i
---
without (it|running|the check|check\.sh)|\bskip
