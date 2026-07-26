# Agent Feedback

How the agentic system learns from correction. This is about skills, rules, agent definitions, and
agent memory, not about feedback on human colleagues, trainers, or clients.

After a user corrects, refines, or externally edits work you produced, complete the requested
result first, then improve whatever owns the behaviour before finishing the turn. Load
`agent-feedback` and apply its counterfactual: with the same information available during the
initial run, would a general change have produced the corrected result? If no, change nothing.

Update exactly one owner, and only for a reusable gap:

- **Skill or rule** when the behaviour is shared across tasks.
- **Agent definition** in `.claude/agents/` when it belongs to one agentic colleague. Route it
  through `hr` as a feedback conversation; the agent's file and its known failure modes are the
  record.
- **Agent memory** in `.claude/agent-memory/` when it is context to carry forward, not a rule.
  Follow `agent-memory`: durable meaning, not motion.

The feedback loop never broadens external-action authority. Detecting or comparing an edited
draft is not approval to act on it.
