---
# M1: no git commit -a, which takes the other author's modified file
type: tool_used
tool: Bash
input_match: 'git commit\b[^"\\]* (-a|-am|-qa|-qam|--all)(?=[\s"\\])'
min: 0
max: 0
arm: both
---
