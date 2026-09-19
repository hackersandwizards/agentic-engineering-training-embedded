---
# T3 (SKILL.md:17): no GNU-only command (timeout, nproc, g-prefixed builds) and no flavor-specific short flag (stat -c/-f, xargs -d, grep -P, find -printf, base64 -w, head -n -N, tar --transform/-s)
type: regex
pattern: '^(?![\s\S]*(?:uname|OSTYPE))[\s\S]*(?:^|\n)[^#\n]*(?:(?:^|[\s;|&(])(?:timeout|nproc|gsed|gdate|gtimeout|gstat|gfind|gtar|gcp|greadlink)(?=[\s;|&)]|$)|\bstat\b[^\n|;&]*\s-(?:c|f)\b|\bxargs\b[^\n|;&]*\s-d\b|\bgrep\b[^\n|;&]*\s-P\b|\bfind\b[^\n|;&]*\s-(?:printf|regextype)\b|\bbase64\b[^\n|;&]*\s-w|\bhead\b[^\n|;&]*-n\s*-\d|\btar\b[^\n|;&]*(?:--(?:transform|xform|sort|mtime|numeric-owner)\b|\s-s\s))'
target: { source: file, path: scripts/release.sh }
match: not_contains
weight: 1
---
