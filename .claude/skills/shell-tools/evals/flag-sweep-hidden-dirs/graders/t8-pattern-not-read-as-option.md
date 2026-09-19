---
# T8 (SKILL.md:24): the check script never hands --legacy-auth (or the variable holding it) to grep or rg as a bare first argument, where a leading dash reads as an option
type: regex
pattern: '^[^#\n]*\b(?:grep|rg)\s+(?:-[a-df-zA-Z]+\s+|--[a-z][a-z-]*(?:=\S+)?\s+)*(?:[''"]?--legacy-auth|"?\$\{?[A-Za-z_][A-Za-z_0-9]*\}?"?(?:\s|$))'
flags: m
target: { source: file, path: scripts/check-flags.sh }
match: not_contains
weight: 2
---
