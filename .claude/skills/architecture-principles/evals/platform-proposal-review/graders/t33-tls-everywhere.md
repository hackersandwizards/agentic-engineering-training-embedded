---
# T33 (SKILL.md:48): TLS everywhere, so the review rejects plain HTTP between services
type: regex
pattern: 'TLS|encrypt'
flags: i
target: { source: file, path: docs/review-platform-2027.md }
match: contains
weight: 0.5
---
