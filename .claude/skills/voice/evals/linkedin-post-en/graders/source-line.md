---
# T166 (content-formula.md:34): one `(Source: Name, date)` attribution line
type: regex
target: { source: file, path: post.md }
match: contains
---
\(Source: [^)\n]+\)
