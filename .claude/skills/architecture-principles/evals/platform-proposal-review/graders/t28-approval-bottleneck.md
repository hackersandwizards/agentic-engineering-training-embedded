---
# T28 (SKILL.md:63): approval bottlenecks and unnecessary process gates are waste, so the review names the three approvals or the change board as a cause of slowness
type: regex
pattern: 'three approvals|3 approvals|approval bottleneck|change (?:advisory )?board|sign-?off|approver'
flags: i
target: { source: file, path: docs/review-platform-2027.md }
match: contains
weight: 0.5
---
