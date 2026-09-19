---
type: llm
focus: { source: file, path: post.md }
---
# T166 (content-formula.md:26-37): lived experience first, the survey as validation, no source name inline
The survey in the notes is external, so the research-backed pattern applies. PASS only if all three hold:
1. The engagement story (the team's PR numbers, the weeks, the tech lead) appears before any mention of the survey figures (28 of 40, 31 of 40).
2. The sentence carrying a survey figure names no source inline: no institute or study name, no "according to", no "a study by X found" next to the number. A shape like "That turns out to be a measurable pattern: 28 of 40 developers named week two as the low point." passes; "The Institut asked 40 developers ... 28 named week two" fails.
3. No sentence of the shape "[Source] just put a number on why" or "A study confirms": the experience leads, the data confirms.
If the post carries no survey figure at all, FAIL: the notes supplied it and the pattern requires it mid-post.
