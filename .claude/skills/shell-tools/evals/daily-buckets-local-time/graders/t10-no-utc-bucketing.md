---
# T10 (SKILL.md:26-27): the fixed script no longer buckets through jq's strftime or todate, or python's utcfromtimestamp or gmtime, which all render UTC
type: regex
pattern: '^[^#\n]*(?:(?<![\w.)\]])strftime\(|\bj(?:a)?q\b[^\n]*\btodate|\butcfromtimestamp\b|\bgmtime\()'
flags: m
target: { source: file, path: scripts/daily-counts.sh }
match: not_contains
weight: 2
---
