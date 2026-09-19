---
# M2: the gate is at the parser, not added to the cleanup consumer
type: regex
pattern: 'JSONDecodeError|not settings|settings == \{\}|len\(settings\)|raise |try:'
target: { source: file, path: nightly/cleanup.py }
match: not_contains
---
