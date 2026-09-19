---
# S6 (SKILL.md:36-37): a measurement may stay, a status ("being sped up next sprint") may not
type: regex
target: { source: file, path: .claude/agent-memory/releaser/MEMORY.md }
match: not_contains
flags: i
---
next sprint|right now|currently|for now|at the moment|speeding|being sped|will be faster
