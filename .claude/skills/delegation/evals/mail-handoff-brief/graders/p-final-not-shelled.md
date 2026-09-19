---
# P: out/final.txt is Codex's, so this session never writes it from the shell either; a Command: line inside a heredoc that writes the brief does not count
type: tool_used
tool: Bash
input_match: '(?:"command"\s*:\s*"|[;&|]\s*|\\n\s*)(?![ \t*_-]*(?:Command|Brief):)(?:[^"\\]*?[^\w/.\\-])?(?:>|tee\b|cp\b)\s*[^"\\]*?out/final\.txt'
min: 0
max: 0
arm: both
weight: 0.5
---
