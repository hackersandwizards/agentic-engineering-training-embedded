# Research and plan a vertical feature

Duration: 75 minutes

## Outcome

The group has an approved implementation plan tied to requirements and
verification before source files change.

## Task

1. Choose a real, bounded feature from your team's repository. Confirm its
   acceptance criteria with the group.
2. Let the agent research the current flow from user or protocol input to the
   observable output. Require file references and affected constraints.
3. Review the research. Correct unsupported assumptions before asking for a
   plan.
4. Require the plan to name exact files, behavior changes, risks, negative
   cases, tests and the final repository gate.
5. Decide what is explicitly out of scope.
6. Approve only when another group member can implement the plan without
   rediscovering the system.

Culina feature options are listed in `m3-01-rpi-group-work.md`. Prefer a
vertical feature that crosses more than one layer but remains demonstrable
within 90 minutes.

## Done when

- Research and plan are separate artifacts.
- Acceptance criteria are observable and testable.
- The plan identifies safety, timing, memory and protocol impact where relevant.
