---
# T24 (SKILL.md:38,59,87): a monolithic frontend both teams commit to is an anti-pattern, so the review wants the UI split by context or team
type: regex
pattern: 'micro[- ]?frontends?|monolithic frontend|frontend monolith|(?:frontend|UI) (?:per|split by|owned by|for each) (?:team|context|domain)|self-contained system|vertical(?:ly)? (?:slice|split|system)|each (?:team|context) (?:owns|ships) (?:its|their) (?:own )?(?:UI|frontend|pages)'
flags: i
target: { source: file, path: docs/review-platform-2027.md }
match: contains
weight: 1
---
