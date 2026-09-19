---
# T10 (personal-voice.md:37, 94, 139-142): `du` throughout, zero formal `Sie`; a capitalised Sie/Ihnen/Ihre mid-sentence is the formal form
type: regex
target: { source: file, path: reply.md }
match: not_contains
---
[a-zäöüß,] (Sie|Ihnen|Ihre|Ihrem|Ihren|Ihrer)\b
