---
# T25 (SKILL.md:38-39,59): events over synchronous calls, so the review answers the four-hop request chain with domain events and eventual consistency
type: regex
pattern: 'domain events?|event[- ]driven|event stream|eventual(?:ly)? consisten|outbox|publish(?:es|ed|ing)? (?:an |the )?events?|asynchronous events?'
flags: i
target: { source: file, path: docs/review-platform-2027.md }
match: contains
weight: 2
---
