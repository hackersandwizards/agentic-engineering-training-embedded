---
# G13: the malformed data file is repaired too
type: regex
pattern: ',\s*\}'
target: { source: file, path: config/settings.json }
match: not_contains
---
