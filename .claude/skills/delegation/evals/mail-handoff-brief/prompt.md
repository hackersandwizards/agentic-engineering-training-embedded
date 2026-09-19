---
runs: 3
max_turns: 40
timeout_seconds: 1200
allowed_tools: [Read, Glob, Grep, Bash, Write, Edit, Skill]
---
out/mail.txt is the draft that `claude -p` produced from brief/facts.md. Codex finishes the delivery from a brief you write, ending with out/final.txt, the text the sender pastes into the mail client (TOOLING.md says how delivery works here). Write plan/deliver.md: one `## Step: <title>` per step Codex takes, under it `Command:` with the exact command line the step runs or `none`, then `Brief:` followed by the complete instruction text Codex receives for that step. Do not change out/mail.txt and do not write out/final.txt: both are Codex's. Nobody is available for questions. Final message: every finding you hold against the draft, each with the draft's line and the fact it conflicts with, and what Codex delivers.
