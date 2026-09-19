---
# S23 (SKILL.md:90): no git add -A/-u/. or commit -a, which take the other author's file into the commit
type: tool_used
tool: Bash
input_match: 'git add (-A|--all|-u|--update|\.|src/?\*?)(?=[\s"\\])|git commit\b[^"\\]* (-a|-am|-qa|-qam|--all)(?=[\s"\\])'
min: 0
max: 0
arm: both
---
