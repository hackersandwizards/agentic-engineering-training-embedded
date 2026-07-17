---
name: improve-skills
description: >-
  Turn follow-up corrections to skill-generated work into minimal reusable skill improvements.
  Use after a user corrects, refines, or externally edits an output, or answers a question the
  skill should have resolved itself, to decide whether the owning skill should change and update
  it without encoding the specific case.
---

# Improve Skills

Complete the user's requested correction first. Then improve a skill only when this
counterfactual is true:

> With the same information available during the initial run, would a general skill change have
> produced the corrected result?

## Classify the feedback

- Improve retrieval or question timing when the missed information was discoverable or should
  have been requested earlier.
- Leave skills unchanged when the user supplied unavailable case facts, changed the goal, or made
  a one-off preference.
- Require an observed before-and-after comparison for changes made outside the conversation. Do
  not infer an improvement from an external action alone.
- When the skill already contains the right instruction, remove conflicts, consolidate it, or add
  a deterministic check. Never append a duplicate reminder.

## Update the owner

1. Locate the canonical skill that owned the failed behavior. Never edit a generated mirror,
   plugin cache, or customer-specific artifact as the source of truth.
2. Search its instructions and related rules for overlap or contradiction.
3. Prefer deletion, then replacement, then addition. Add only a new reusable invariant; never add
   the concrete customer, artifact, wording, answer, or outcome.
4. Keep one owner per behavior. Prefer a test, validator, or script over more prose when the
   requirement is deterministic.
5. Validate the skill and the affected workflow with the repository's checks. Forward-test only
   when it cannot mutate live systems or require new approval.

For canonical global files under `~/.claude/rules` or `~/.claude/skills`, run
`~/.claude/scripts/sync-agent-config.sh` after validation so the configured repositories receive
and commit and push the mirrors.

## Preserve action boundaries

Feedback and review never authorize an external action. In particular, detecting, reading, or
comparing an edited email draft never authorizes sending it. Send only when the current user
prompt explicitly orders sending that specific draft; otherwise leave it as a draft.

Report a completed improvement in one line naming the skill and the generalized change. If the
counterfactual fails, continue without a skill edit.
