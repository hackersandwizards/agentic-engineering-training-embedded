---
# T24 (SKILL.md:52): the runbook previews the notes with bun, not node or npm
type: regex
pattern: '(?:^|[\s`$(])bun\s+(?:run\s+)?(?:\S*render-notes\.js|notes\b)'
flags: m
target: { source: file, path: RELEASE.md }
match: contains
weight: 1
---
