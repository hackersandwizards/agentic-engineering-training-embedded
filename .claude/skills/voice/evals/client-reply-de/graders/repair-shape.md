---
type: llm
focus: { source: file, path: reply.md }
---
# T101 (postures.md:116-125): the slides miss has the repair shape, short, owned, fixed in the same breath
Find the passage about the slides (Slides, Folien, Unterlagen). PASS only if all three hold:
1. The miss is owned in at most two short sentences and at most 15 words in total, with `sorry`, `mein Fehler`, `liegt an mir`, `auf meine Kappe` or an interjection like `Ah` or `Mist`.
2. The fix (they go out today) sits in the same passage, in at most one short sentence.
3. No `aber` after the owning, no promise about the future ("passiert nicht wieder"), no `Entschuldigung`, no `tut mir leid, dass ihr warten musstet`.
FAIL if the passage runs over 15 words before the fix, or if the owning is followed by a defence or an explanation of how it happened. The cause is not this grader's question; do not fail on the trainer being named.
