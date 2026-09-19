---
# T27 (SKILL.md:62): heroism culture is process waste, so the review names the praised night-time fixes as a problem rather than an asset
type: regex
pattern: 'hero(?:ism|ic|es)?\b|3 ?am|at night|night[- ]time|from his phone|single point of failure|bus factor|only (?:Ben|one person) knows'
flags: i
target: { source: file, path: docs/review-platform-2027.md }
match: contains
weight: 1
---
