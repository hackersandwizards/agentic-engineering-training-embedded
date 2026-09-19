---
# T3 (SKILL.md:17): the script never parses or shifts a date with date -d, --date, -j, -v, -r or -f, which exist on one flavor only; the previous release date comes from git or python
type: regex
pattern: '^(?![\s\S]*(?:uname|OSTYPE|date --version))[\s\S]*(?:^|\n)[^#\n]*\bdate\b[^\n|;&]*(?:\s-(?:d|j|r|f)\b|\s-v[-+]?\d|\s--[a-z])'
target: { source: file, path: scripts/release.sh }
match: not_contains
weight: 2
---
