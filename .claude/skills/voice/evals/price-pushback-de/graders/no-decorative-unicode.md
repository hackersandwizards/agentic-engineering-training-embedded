---
# T15, T22, T84 (personal-voice.md:95-97, 131-133; brand-voice.md:225-239): no dashes, semicolons, curly quotes, ellipsis, arrows, bullets, pictograph emoji; `;)` stays
type: regex
target: { source: file, path: reply.md }
match: not_contains
---
[—–…“”„‘’→←•·]|;(?!\))|[\uD83C-\uD83E][\uDC00-\uDFFF]|[☀-➿]
