---
# T7 (SKILL.md:23): no rg call carries -r in a short flag cluster, which is --replace and rewrites the output
type: tool_used
tool: Bash
input_match: '(?<!#[^\\]*)\brg\s+(?:-[a-zA-Z]+\s+|--[a-z][a-z-]*\s+)*-[a-zA-Z]*r[a-zA-Z]*(?=\s)'
min: 0
max: 0
arm: both
weight: 2
---
