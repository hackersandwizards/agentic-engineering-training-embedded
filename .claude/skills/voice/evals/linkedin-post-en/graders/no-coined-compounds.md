---
# T69 (ai-tells.md:212-218): the invented compact noun and the hyphenated re- verb
type: regex
target: { source: file, path: post.md }
match: not_contains
flags: i
---
\b(load-bearing|chokepoint|tripwire|backstop|carve-out|ratchet|re-verif\w*|re-deriv\w*|re-measur\w*|re-check\w*|re-confirm\w*|re-read)\b
