---
# M2: the gate is at the parser, not added to the notify consumer
type: regex
pattern: 'JSONDecodeError|not settings|settings == \{\}|len\(settings\)|raise |try:'
target: { source: file, path: nightly/notify.py }
match: not_contains
---
