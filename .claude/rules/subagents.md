# Subagents

- Delegate when: (a) a task spans 3+ files, (b) research could fill the main context, (c) multiple independent queries can run in parallel.
- One task per subagent for focused execution.
- Running unattended, say so in every subagent prompt you write. A fresh delegate inherits none of your context and will otherwise stop to ask.
- Fan out at most 3 subagents at a time; ask before spawning more. An unattended run sends the rest in a later batch instead of asking, never absorbing their work itself. Applies doubly in ultra mode, where every extra agent chews quota.
- Before building or changing Claude Code artifacts (skills, rules, subagents, hooks, output styles, settings, MCP), consult the `claude-code-guide` agent or official docs. Don't guess the frontmatter or mechanics from memory.
