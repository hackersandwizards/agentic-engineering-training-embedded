# Connect the Agentic SDLC into a factory loop

Duration: 60 minutes split across two blocks

## Outcome

The group can place agents across refinement, planning, implementation, review
and operations without turning one agent into an unbounded automation system.

## Task

1. Start from one Culina feature brief. Use an agent to refine it into observable
   acceptance criteria, explicit exclusions and unanswered product decisions.
2. Route the approved brief through research and planning. Use the custom agents
   to review the plan and implementation by concern.
3. Draw the deterministic sequence: inputs, agent or skill, allowed tools,
   produced artifact, verification and human decision. Mark every stop condition.
4. Design a PR-babysitting or scheduled-agent job that observes CI, classifies a
   failure and prepares a proposed next action. It must not merge, weaken a gate
   or edit an approval record.
5. Run the smallest safe part of the sequence. Simulate external triggers when
   the training environment has no suitable repository or scheduler.
6. Map the same sequence to one task in the team's normal repository.

## Done when

- Refinement, planning, implementation and review each have a named input and
  output.
- The sequence fails closed when evidence or authority is missing.
- The scheduled-agent design names its trigger, permissions, stop condition and
  human handoff.
- The team can identify which parts are deterministic orchestration and which
  require model judgment.
