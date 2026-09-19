---
# T21 (SKILL.md:44): trunk-based development and deploy on every green build, so the review answers gitflow with trunk-based delivery
type: regex
pattern: 'trunk|every green build|continuous deployment|deploy(?:s|ed|ing)? (?:on )?(?:each|every) (?:green|merge|commit)'
flags: i
target: { source: file, path: docs/review-platform-2027.md }
match: contains
weight: 2
---
