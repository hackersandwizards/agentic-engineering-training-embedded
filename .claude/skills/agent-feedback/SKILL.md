---
name: agent-feedback
description: >-
  Turn a correction into a lasting improvement of the agentic system: skills, rules, agent
  definitions, and agent memory. Use when authoring, reviewing, trimming, splitting, or rightsizing
  one of those artifacts, and after a user corrects, refines, or externally edits agent-generated
  work, or answers a question the system should have resolved itself, to decide which artifact
  should change and update it without encoding the specific case. Not about feedback on human
  colleagues, trainers, or clients.
---

# Agent Feedback

## Shape

- **Progressive disclosure by default.** When an artifact outgrows one file, split it and route
  from `SKILL.md` by phase or layer.
- **Always-on status is earned.** A rule that fires on a minority of turns gets `paths:`
  frontmatter or becomes a skill. Reference material is never always-on.
- **Design the interface instead of adding examples.** Examples constrain the exploration space;
  an expressive parameter, enum, or validator removes the need for the instruction.

Write for a literal reader.

- Positive imperatives with explicit objects.
- Keep a negative that carries the rule negative; the failure mode is what makes it enforceable.
- Replace vague adverbs ("usually", "as appropriate", "when relevant") with the actual condition.
- Cut the history that produced the rule: version changes, vendor incidents, prior bugs, stability
  caveats, and verification counts. Keep the failure mode only where it makes the rule enforceable.
- English for the instruction; quoted examples keep their own language.

## Improve

Complete the user's requested correction first. Then change an artifact only when this
counterfactual is true:

> With the same information available during the initial run, would a general change have
> produced the corrected result?

If no, change nothing.

## Pick the owner

Exactly one, and only for a reusable gap:

- **Skill or rule** when the behaviour is shared across tasks or agents.
- **Agent definition** in `.claude/agents/` when it belongs to one agentic colleague. Route it
  through the `hr` agent as a feedback conversation; that agent's file and its known failure modes
  are the record.
- **Agent memory** in `.claude/agent-memory/` when it is context to carry forward rather than a
  rule.

Feedback and review never authorize an external action. Detecting, reading, or comparing an edited
draft is not approval to act on it.

## Classify the feedback

- Improve retrieval or question timing when the missed information was discoverable or should
  have been requested earlier.
- Leave the artifact unchanged when the user supplied unavailable case facts, changed the goal, or
  made a one-off preference.
- Require an observed before-and-after comparison for changes made outside the conversation. Do
  not infer an improvement from an external action alone.
- When the artifact already contains the right instruction, remove conflicts, consolidate it, or
  add a deterministic check. Never append a duplicate reminder.

## Update it

1. Locate the canonical artifact that owned the failed behavior. Never edit a generated mirror,
   plugin cache, or customer-specific artifact as the source of truth.
2. Search its instructions, related rules, and the harness system prompt for overlap or
   contradiction. While there, remove the no-ops, kill duplication, and take out anything
   irrelevant; leave the file leaner than you found it.
3. Prefer deletion, then replacement, then addition. Add only a new reusable invariant; never add
   the concrete customer, artifact, wording, answer, or outcome.
4. Keep one owner per behavior. Prefer a test, validator, or script over more prose when the
   requirement is deterministic.
5. Validate the artifact and the affected workflow with the repository's checks. Forward-test only
   when it cannot mutate live systems or require new approval.

For canonical global files under `~/.claude/rules` or `~/.claude/skills`, run
`~/.claude/scripts/sync-agent-config.sh` after validation so the configured repositories receive
the mirrors, then commit and push them.

Report a completed improvement in one line naming the artifact and the generalized change.
