---
# T51, T55, T56, T61, T62, T87, T105 (ai-tells.md:20, 42, 48, 101, 111; postures.md:32, 134): German reframe, announced count, soft-challenge, bridge filler, copula dodge, `Kein Problem` as a standalone reply, `macht das Sinn`
type: regex
target: { source: file, path: reply.md }
match: not_contains
---
[Nn]icht nur [^.\n]{1,60}, sondern|[Ll]etzten Endes|[Ii]m Grunde|[Ii]m Kern|[Nn]ichtsdestotrotz|in der Tat|fungiert als|stellt [^.\n]{1,40} dar\b|Drei Dinge|Zwei Punkte|[Ee]in paar Gedanken|(^|\n|[.!?] )Kein Problem|würde ich nachhaken|würde ich rütteln|[Mm]acht das Sinn
