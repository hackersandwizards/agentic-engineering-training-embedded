---
runs: 3
max_turns: 40
timeout_seconds: 900
allowed_tools: [Read, Glob, Grep, Bash, Write, Edit, Skill]
---
The pkgctl skill in agent-config/skills/pkgctl has grown fat. Cut it down to what `bin/pkgctl --help` does not already say, drop the yank mode entirely (we do not yank versions any more), and make it stand on its own without pointing at other files. Commit. Nobody answers questions in this session.
