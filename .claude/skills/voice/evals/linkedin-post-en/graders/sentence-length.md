---
# T38 (prose-style.md:8-9): main clauses 15-20 words, hard ceiling 26, so no sentence of 27 words or more
# A word is a run of non-space characters. A sentence ends at `.`, `!` or `?` followed by a space, or at the end of the line, so `CLAUDE.md` stays one word
type: regex
target: { source: file, path: post.md }
match: not_contains
---
(?:(?:[^\s.!?]|[.!?](?=\S))+[ \t]+){26,}(?:[^\s.!?]|[.!?](?=\S))+
