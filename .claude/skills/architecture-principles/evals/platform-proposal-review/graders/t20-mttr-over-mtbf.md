---
# T20 (SKILL.md:30): MTTR over MTBF, so the review answers the reliability section with recovery time rather than the proposed regression window
type: regex
pattern: 'MTTR|mean time to (?:recover|restor|repair)|time to (?:recover|restore|repair)|recovery time|(?:recover|restore|roll back|rollback) (?:in|within|under|fast|quickly|in minutes)'
flags: i
target: { source: file, path: docs/review-platform-2027.md }
match: contains
weight: 2
---
