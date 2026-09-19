---
# T4 (SKILL.md:69-70): build or buy is evaluated on functional, technical and operational complexity plus unique business value
type: regex
pattern: '^(?=[\s\S]*functional complexity)(?=[\s\S]*technical complexity)(?=[\s\S]*operational complexity)(?=[\s\S]*(?:unique business value|differentiat|core business|competitive))'
flags: i
target: { source: file, path: docs/adr/0004-customer-notifications.md }
match: contains
weight: 1
---
