---
# T68 (ai-tells.md:206-210): adjudication register in a post; the plain word instead
type: regex
target: { source: file, path: post.md }
match: not_contains
flags: i
---
\b(refusal|premise|ruling|asymmetry|defects?|precedent|remedy|verdict|caveat|hazard)\b
