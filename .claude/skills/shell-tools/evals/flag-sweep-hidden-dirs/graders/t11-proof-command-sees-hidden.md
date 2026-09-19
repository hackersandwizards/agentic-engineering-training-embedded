---
# T11 (SKILL.md:28): the proof command in SWEEP.md is not an rg run without --hidden, -uu, -. or a named dot-path, which cannot fail on the hidden files
type: regex
pattern: '(?:^\s*(?:\$\s*)?|^[^\n`]*[;&|]\s*)rg\s+(?=[''"-])(?![^\n]*(?:--hidden|-uu|\s-\.(?:\s|$)|\s\.[A-Za-z]))'
flags: m
target: { source: file, path: SWEEP.md }
match: not_contains
weight: 2
---
