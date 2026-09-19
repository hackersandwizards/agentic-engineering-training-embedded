---
# G2: the loader's caller is read before the loader is changed
type: regex
target: trace
match: contains
pattern: 'nightly/cleanup\.py'
weight: 0.5
---
