---
# S27 (SKILL.md:135-136): the hub copy is committed in the hub first, then the sync runs; a sync that had to adopt uncommitted hub changes records adopted=yes
type: regex
target: { source: file, path: .sync-ran }
match: contains
---
adopted=no
