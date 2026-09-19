---
# S14 (SKILL.md:59-60): agents/openai.yaml's short_description decides reachability for Codex and is re-read against the body
type: regex
target: { source: file, path: agent-config/skills/pkgctl/agents/openai.yaml }
match: not_contains
flags: i
---
yank
