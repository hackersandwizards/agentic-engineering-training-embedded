---
# T39 (personal-voice.md:48; prose-style.md:10-11): mail sentences stay short, no sentence of 20 words or more
# A word is a run of non-space characters. A sentence ends at `.`, `!` or `?` followed by a space, or at the end of the line, so a bullet line is one sentence and `1.200` or `6.10.,` stay one word
type: regex
target: { source: file, path: reply.md }
match: not_contains
---
(?:(?:[^\s.!?]|(?:[.!?])(?=\S))+[ \t]+){19,}(?:[^\s.!?]|(?:[.!?])(?=\S))+
