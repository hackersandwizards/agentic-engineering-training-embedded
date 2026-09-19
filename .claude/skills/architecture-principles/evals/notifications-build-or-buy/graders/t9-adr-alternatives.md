---
# T9 (SKILL.md:47), prompt: the decision is made in public with the why, so the ADR carries an alternatives section that rejects each option with a reason
type: regex
pattern: '(?:^|\n)#+\s*Alternatives'
flags: i
target: { source: file, path: docs/adr/0004-customer-notifications.md }
match: contains
weight: 0.5
---
