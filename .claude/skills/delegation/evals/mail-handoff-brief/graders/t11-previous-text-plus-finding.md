---
# T11 (SKILL.md:39-41): the corrected text comes from a claude -p call given the previous text plus the findings; Codex never applies a correction to the words itself
type: llm
focus: { source: file, path: plan/deliver.md }
weight: 2
---
Read the brief as Codex would. The one question: does the corrected mail text come out of a `claude -p` call that receives the previous draft (inline, by file, or by an instruction to pass it) together with the concrete findings (the weekday and the link), with no step telling Codex to change, fix, correct, rewrite or polish any word of the draft itself? PASS if yes. FAIL if Codex is told to apply a correction by editing the text, if the second call starts from the facts alone without the previous text, or if the brief lets Codex change wording, casing or sentences on its own.
