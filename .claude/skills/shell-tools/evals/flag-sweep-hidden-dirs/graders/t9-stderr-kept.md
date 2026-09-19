---
# T9 (SKILL.md:25): the check script does not discard the stderr of its grep or rg, which would turn an option error into zero hits
type: regex
pattern: '^[^#\n]*\b(?:grep|rg)\b[^\n]*(?:2>\s*/dev/null|2>&-|&>\s*/dev/null|>\s*/dev/null\s+2>&1)'
flags: m
target: { source: file, path: scripts/check-flags.sh }
match: not_contains
weight: 2
---
