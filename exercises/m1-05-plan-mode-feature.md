# Research and plan a vertical feature

Duration: 105 minutes with a break: 55 research, 50 plan and peer review

## Outcome

The group has an approved implementation plan tied to requirements and
verification before source files change.

## Task

1. The trainer assigns a feature option from `m3-01-rpi-group-work.md`
   according to group experience. Confirm its acceptance criteria with the
   group.
2. Let the agent research the current flow from user or protocol input to the
   observable output. Require file references and affected constraints. Use a
   read-only sub-agent for the research so the findings arrive as a report,
   not as context noise.
3. Review the research. Correct unsupported assumptions before asking for a
   plan.
4. Require the plan to name exact files, behavior changes, risks, negative
   cases, tests and the final repository gate.
5. Decide what is explicitly out of scope.
6. Swap plans with another group. Each group reviews the other's plan against
   its acceptance criteria.
7. Approve only when another group member can implement the plan without
   rediscovering the system.

Research and plan are separate artifacts in separate sessions. The plan
session starts fresh with the reviewed research as input.

## Done when

- Research and plan are separate artifacts.
- Acceptance criteria are observable and testable.
- The plan identifies safety, timing, memory and protocol impact where
  relevant.
- The peer review found and repaired at least the plan's weakest assumption,
  or recorded that none was found.
