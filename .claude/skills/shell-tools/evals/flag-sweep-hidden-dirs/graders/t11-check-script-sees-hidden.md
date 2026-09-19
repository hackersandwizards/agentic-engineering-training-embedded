---
# T11 (SKILL.md:28): the check script does not sweep with an rg that skips hidden paths, so a flag reappearing under .github/ would fail CI
type: regex
pattern: '^(?:[^#\n]*(?:[;&|(]|\bif|\bthen|\bdo|!)\s*|\s*)rg\s+(?=[''"-])(?![^\n]*(?:--hidden|-uu|\s-\.(?:\s|$)|\s\.[A-Za-z]))'
flags: m
target: { source: file, path: scripts/check-flags.sh }
match: not_contains
weight: 2
---
