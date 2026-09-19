---
# F5 (failure-modes.md:21-22): the sweep covers <!-- --> comments
type: regex
pattern: '<!-- header -->|<!-- main content -->'
target: { source: file, path: docs/index.html }
match: not_contains
weight: 0.5
---
