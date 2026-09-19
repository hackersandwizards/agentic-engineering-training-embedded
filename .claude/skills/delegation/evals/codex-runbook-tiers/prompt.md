---
runs: 3
max_turns: 40
timeout_seconds: 1200
allowed_tools: [Read, Glob, Grep, Bash, Write, Edit, Skill]
---
The team runs the work in this repository through `codex exec`. Write the runbook at plan/runbook.md for the pieces in ISSUES.md and brief/client-mail.md, in this order and with exactly these titles: `race fix` (issue 41), `json flag` (issue 42), `readme typo` (issue 43), `final review` (the combined diff of the three fixes before merge), `eval run` (evals/run.py over all 40 cases, 3 runs each, on the fixed code), `client mail` (the mail described in brief/client-mail.md).

One `## Step: <title>` per piece. Under it: `Command:` with the exact command line the team runs, `Model:` with the model id the step runs on, `Effort:` with the reasoning effort, both written out as values (never `default`, never left to the config), then `Brief:` followed by the complete prompt text the command receives. Change no file other than plan/runbook.md. Nobody is available for questions. Final message: the steps with model and effort each, and every decision you made that the pieces left open.
