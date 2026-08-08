# Subagents

- Delegate when: (a) a task spans 3+ files, (b) research could fill the main context, (c) multiple independent queries can run in parallel.
- One task per subagent for focused execution.
- Running unattended, say so in every subagent prompt you write. A fresh delegate inherits none of your context and will otherwise stop to ask.
- Outbound mail an unattended run produces is drafted by the `assistant` agent, who signs it in his own name. Decide the case and write the records yourself, then hand him the recipient, the thread, the facts, and the skill section that constrains the draft. Run by hand, the same workflow drafts in the requester's name.
- Fan out at most 3 subagents at a time; ask before spawning more. An unattended run sends the rest in a later batch instead of asking, never absorbing their work itself. Applies doubly in ultra mode, where every extra agent chews quota.
- Before building or changing Claude Code artifacts (skills, rules, subagents, hooks, output styles, settings, MCP), consult the `claude-code-guide` agent or official docs. Don't guess the frontmatter or mechanics from memory.
- A scheduled task carries only what is true because it runs on a schedule: the cadence, the colleague it delegates to, the standing approval and its limit, and the ledger that dedupes across runs. Put the procedure in a skill the task loads. Test it by deleting the task: if the work is then unrunnable by hand, the procedure sits in the wrong file.
