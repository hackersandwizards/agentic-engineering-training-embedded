---
# T29 (SKILL.md:63-64): oversized work packages and unfinished tickets are waste, so the review reads the tickets and names the 21- and 34-point work open since June
type: regex
pattern: '(?:21|34)[- ]point|oversized|too (?:big|large)|large (?:tickets|batches|work packages)|epics? (?:as|is|are) (?:one|a single) ticket|unfinished|work in progress|WIP|in progress (?:since|for) |open since June|no (?:wip|work[- ]in[- ]progress) limit'
flags: i
target: { source: file, path: docs/review-platform-2027.md }
match: contains
weight: 1
---
