---
# T10 (SKILL.md:26-27): the fixed script names Europe/Berlin, the zone the days are counted in, since local time is whatever TZ the caller has
type: regex
pattern: 'Europe/Berlin'
target: { source: file, path: scripts/daily-counts.sh }
match: contains
weight: 1
---
