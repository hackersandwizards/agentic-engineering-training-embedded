---
# T3 (SKILL.md:17): the script never uses bare sed -i or sed -i '', which GNU and BSD sed parse differently; a suffix form (-i.bak) or a temp file is portable
type: regex
pattern: '^(?![\s\S]*(?:uname|OSTYPE|sed --version))[\s\S]*(?:^|\n)[^#\n]*\bsed\b[^\n|;&]*\s(?:-[a-hj-zA-Z]*i(?:\s*''''|\s|$)|--in-place(?:\s|$))'
target: { source: file, path: scripts/release.sh }
match: not_contains
weight: 2
---
