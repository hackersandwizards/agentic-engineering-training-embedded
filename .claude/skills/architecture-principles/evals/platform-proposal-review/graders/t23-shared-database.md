---
# T23 (SKILL.md:38,59): a shared database across team boundaries is an anti-pattern, so the review names the integration database and wants data owned per context
type: regex
pattern: 'shared (?:postgres|database|db|schema|tables?)|integration database|(?:database|data|tables?|schema) (?:per|owned by|of its own)|own(?:s|ed)? (?:its|their) (?:own )?(?:data|database|tables?|schema)'
flags: i
target: { source: file, path: docs/review-platform-2027.md }
match: contains
weight: 1
---
