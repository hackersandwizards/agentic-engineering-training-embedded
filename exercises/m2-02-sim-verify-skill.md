# Turn verification into a reusable workflow

Duration: 25 minutes

## Outcome

The successful verification path from the feature becomes a reusable workflow
that reports evidence and limitations.

## Task

1. Start with the commands that actually proved the group feature.
2. Package the sequence using the mechanism supported by your coding agent.
3. Run the narrow behavioral test first, then the relevant integration or
   simulation evidence, then the full repository gate.
4. Make the report include commands, exit status, relevant output and any layer
   that was not exercised.
5. Demonstrate that the workflow fails when its chosen test is intentionally
   given an impossible expectation. Revert that temporary change immediately.

For Culina, `./scripts/gate.sh` is the final gate. A focused workflow should
still select the relevant GoogleTest and scenario before paying the full cost.

## Done when

- The workflow reproduces the evidence from the completed feature.
- It fails clearly on a temporary negative control.
- It describes simulation as model evidence, not hardware validation.
