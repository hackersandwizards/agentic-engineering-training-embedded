---
# T3 (SKILL.md:17): the fix does not convert epochs with date -r or date -d, which exist on one flavor only
type: regex
pattern: '^(?![\s\S]*(?:uname|OSTYPE|date --version))[\s\S]*(?:^|\n)[^#\n]*\bdate\b[^\n|;&]*(?:\s-(?:d|j|r|f)\b|\s-v[-+]?\d|\s--[a-z])'
target: { source: file, path: scripts/daily-counts.sh }
match: not_contains
weight: 1
---
