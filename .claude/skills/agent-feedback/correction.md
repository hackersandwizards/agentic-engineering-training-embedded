# Turn a correction into an improvement

Entered only after a correction has happened. Classification decides whether there is anything to
own, so it runs before the owner is picked. Writing the edit follows the shape rules in
[SKILL.md](SKILL.md).

## Improve

Complete the user's requested correction first. Then change an artifact only when this
counterfactual is true:

> With the same information available during the initial run, would a general change have
> produced the corrected result?

If no, change nothing.

## Classify the feedback

- Improve retrieval or question timing when the missed information was discoverable or should
  have been requested earlier.
- Leave the artifact unchanged when the user supplied unavailable case facts, changed the goal, or
  made a one-off preference.
- Require an observed before-and-after comparison for changes made outside the conversation; never
  infer an improvement from an external action alone.
- When the artifact already contains the right instruction, remove conflicts, consolidate it, or
  add a deterministic check. Never append a duplicate reminder.

## Pick the owner

Exactly one, and only for a reusable gap:

- **Skill or rule** when the behaviour is shared across tasks or agents.
- **Project instructions** in `CLAUDE.md` when it binds every task in one repository.
- **Agent definition** in `.claude/agents/` when it belongs to one agentic colleague. The project's
  own instructions, its rules, or the agent file itself name who owns those files: read that before
  editing one, and where an owner is named the edit is theirs, so report the gap instead.
- **Agent memory** in `.claude/agent-memory/` when it is context to carry forward rather than a
  rule.

## Update it

1. Locate the canonical artifact that owned the failed behavior. Never edit a generated mirror,
   plugin cache, or customer-specific artifact as the source of truth, and check it against the
   mirror arrays under `## Mirrors and sync` in [SKILL.md](SKILL.md) before editing.
2. Search its instructions, related rules, and the harness system prompt for overlap or
   contradiction. While there, remove the no-ops, kill duplication, and take out anything
   irrelevant.
3. Add only a new reusable invariant; never add the concrete customer, work product, wording,
   answer, or outcome.
4. Validate the artifact and the affected workflow with the repository's checks. Forward-test only
   when it cannot mutate live systems or require new approval.

Report a completed improvement in one line naming the artifact and the generalized change.
