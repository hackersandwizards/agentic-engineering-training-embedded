---
# T7 (SKILL.md:23): the override is per invocation, so the model key in .codex/config.toml still names no luna model
type: regex
pattern: '^\s*model\s*=\s*"[^"]*luna'
flags: im
target: { source: file, path: .codex/config.toml }
match: not_contains
weight: 0.5
---
