---
# T5 (personal-voice.md:25): Benedikt opens `Moin <Vorname>,`, whatever the client's own opener was
type: regex
target: { source: file, path: reply.md }
match: contains
---
(^|\n)Moin Tessa,
