---
# T14 (SKILL.md:48): the plan carries a step that sets the alt text the run left undone to the 1.4 value
type: regex
pattern: 'alt[^\n]{0,60}(?:to|=|:)[^\n]{0,40}1\.4|Hero image for release 1\.4'
flags: i
target: { source: file, path: plan/delegation.md }
match: contains
weight: 0.5
---
