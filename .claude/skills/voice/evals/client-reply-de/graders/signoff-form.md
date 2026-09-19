---
# T6, T8 (personal-voice.md:26-27, 32-33): `Liebe Grüße`, newline, `/bene`; no comma, no `Bene`
type: regex
target: { source: file, path: reply.md }
match: contains
---
Liebe Grüße[ \t]*\n[ \t]*/bene
