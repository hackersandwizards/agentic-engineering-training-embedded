---
# T3 (SKILL.md:17): no GNU long option on a coreutils command BSD builds reject (wc, mkdir, cp, date, sed, stat, cut, tr, du, df, cat, touch, chmod, ln, rm, ls, find, basename, dirname, readlink)
type: regex
pattern: '^(?![\s\S]*(?:uname|OSTYPE))[\s\S]*(?:^|\n)[^#\n]*(?:^|[\s;|&(])(?:sed|date|stat|wc|cp|mv|rm|ls|find|mkdir|touch|cut|tr|du|df|cat|tee|chmod|ln|basename|dirname|readlink)\b[^\n|;&]*\s--[a-z]'
target: { source: file, path: scripts/release.sh }
match: not_contains
weight: 1
---
