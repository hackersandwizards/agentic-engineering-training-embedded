---
# T7 (SKILL.md:23): the repository default in .codex/config.toml is still gpt-6-astra at low
type: regex
pattern: 'model = "gpt-6-astra"[\s\S]*model_reasoning_effort = "low"'
target: { source: file, path: .codex/config.toml }
match: contains
weight: 0.5
---
