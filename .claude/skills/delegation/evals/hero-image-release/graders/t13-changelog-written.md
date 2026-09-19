---
# T13 (SKILL.md:45): the changelog entry is written in this session, which happens only where the step stayed with self
type: regex
pattern: '##\s*\[?v?1\.4'
target: { source: file, path: CHANGELOG.md }
match: contains
weight: 0.5
---
