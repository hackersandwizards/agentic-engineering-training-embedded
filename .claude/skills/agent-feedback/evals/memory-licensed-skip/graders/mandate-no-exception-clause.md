---
# S20, S23 (SKILL.md:92-96, 106-112): the widening is written by splitting acts, never by appending an exception
type: regex
target: { source: file, path: agent-config/agents/releaser.md }
match: not_contains
flags: i
---
\b(except|unless|exception)\b
