# Subagents

- Delegate when: (a) a task spans 3+ files, (b) research could fill the main context, (c) multiple independent queries can run in parallel.
- One task per subagent for focused execution.
- Fan out at most 3 subagents at a time; ask before spawning more. Applies doubly in ultra mode, where every extra agent chews quota.
- Before building or changing Claude Code artifacts (skills, rules, subagents, hooks, output styles, settings, MCP), consult the `claude-code-guide` agent or official docs. Don't guess the frontmatter or mechanics from memory.
