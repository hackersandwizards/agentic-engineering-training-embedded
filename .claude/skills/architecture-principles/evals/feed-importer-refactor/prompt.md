---
runs: 3
max_turns: 60
timeout_seconds: 1800
allowed_tools: [Read, Glob, Grep, Bash, Write, Edit, Skill]
---
The feed importer under importer/ has become hard to change: the last two feed format changes each took a week and touched every file. Restructure it so that the next format change is small. Behaviour stays the same. Tests run with `python3 -m unittest` and must stay green; adjust them only where an interface you changed forces it. Don't commit, I will review the diff. Tell me what you changed and why, and end your message with the output of `git status --short`.
