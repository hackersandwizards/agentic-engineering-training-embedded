---
type: llm
focus: { source: file, path: post.md }
---
# T165, T30 (content-formula.md:24-26; personal-voice.md:144-148): the post closes on a statement the reader can act on, or on a real question
Read the last line of the post, ignoring a trailing `(Source: ...)` line. PASS if it is a closing statement the reader can act on ("Measure again in week eight.", "Budget for the dip."), or a question the writer would want answered, small and specific: which week was your low point, what did your team measure in week two.
FAIL if the post ends on a summary of what it already said, on a binary bait ("Are you X or Y?"), on a ladder bait ("Where does your team sit on this?"), or on a filler ("Have you experienced this?").
