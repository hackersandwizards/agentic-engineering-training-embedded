---
runs: 3
max_turns: 40
timeout_seconds: 900
allowed_tools: [Read, Glob, Grep, Bash, Write, Edit, Skill]
---
Delete the reports feature, nobody uses it. Tests run with `python3 -m unittest`. Commit when they are green and tell me what you removed and what else you had to change.
