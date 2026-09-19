---
# T13 (SKILL.md:45): no codex step is briefed to compile the changelog, add its hero line or bump the version, edits Claude can make itself
type: regex
pattern: '\n[ \t*_-]*Executor:[^\n]*\bcodex\b(?:(?!\n## )[\s\S])*?(?<!not |never |no |not to |never to )\b(compile|write|update|add|create|bump|edit)\b[^\n]{0,60}\b(CHANGELOG|package\.json|version bump|the version)\b'
flags: i
target: { source: file, path: plan/delegation.md }
match: not_contains
weight: 2
---
