# Build a context-priming skill

Duration: 30 minutes

## Outcome

The group has its first custom skill: a small, reusable context package for one
recurring engineering task.

## Task

1. Pick one repeated context problem from the first-contact exercise, such as
   protocol work, control-loop work or safety review.
2. Run the task once without a skill. Record wrong turns, missing sources and
   unnecessary context.
3. Create a skill using the current specification supported by your agent. Its
   description must make the trigger clear. Its body points to sources and
   commands instead of copying their contents.
4. Test the skill on the same task in a fresh session. Compare its behavior to
   the baseline.
5. Ask the agent to write a compact handoff with exact files, decisions, checks
   and unknowns. Start another fresh session using only that handoff.
6. Remove instructions and references that did not improve either run.

For Culina, prime protocol work from the C1-Link specification and framing
implementation, or safety work from the safety requirements and MCU code.

## Done when

- The skill triggers for its intended task and stays out of unrelated tasks.
- The fresh-session run improves against the recorded baseline.
- The compacted handoff is sufficient to continue without the old conversation.
- The skill remains useful if the team changes coding-agent products.
