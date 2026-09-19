---
runs: 3
max_turns: 40
timeout_seconds: 900
allowed_tools: [Read, Glob, Grep, Bash, Write, Edit, Skill]
---
The nightly cleanup has been deleting files younger than 30 days although config/settings.json sets retention_days to 30. I found a trailing comma in that file. Fix the bug in the config loader and add a test. Tests run with `python3 -m unittest`. Tell me what was wrong, what you changed, and what else I need to look at.
