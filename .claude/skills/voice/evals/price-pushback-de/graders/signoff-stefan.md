---
# T14 (personal-voice.md:49): `Viele Grüße, Stefan` on one line
type: regex
target: { source: file, path: reply.md }
match: contains
---
\nViele Grüße, Stefan[ \t]*(\n\s*)?$
