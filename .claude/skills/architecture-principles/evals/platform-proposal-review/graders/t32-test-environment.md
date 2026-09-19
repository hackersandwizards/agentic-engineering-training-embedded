---
# T32 (SKILL.md:58): missing test environments is an anti-pattern, so the review rejects decommissioning staging
type: regex
pattern: 'staging|test environment'
flags: i
target: { source: file, path: docs/review-platform-2027.md }
match: contains
weight: 0.5
---
