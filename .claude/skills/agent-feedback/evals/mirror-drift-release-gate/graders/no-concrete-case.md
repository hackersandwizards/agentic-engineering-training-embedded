---
# C15 (correction.md:65-66), S5 (SKILL.md:34-35): the artifact gains the invariant, never the version, the checkout or the lint incident
type: regex
target: { source: file, path: hub/skills/deploy/release.md }
match: not_contains
flags: i
---
1\.4\.0|lint|flaky|\balpha\b|incident
