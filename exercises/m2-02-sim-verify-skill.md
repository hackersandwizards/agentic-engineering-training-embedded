# Turn verification into a reusable skill

Duration: 30 minutes

## Outcome

The verification path that proved the morning's added tests becomes the second
custom skill. It reports evidence and limitations, then verifies the day-two
feature.

## Task

1. Start with the commands that actually proved the morning's work: the focused
   test, the relevant scenario and the complete build available at this point.
2. Package the sequence using the skill mechanism supported by your coding
   agent.
3. Run the narrow behavioral test first, then relevant simulation evidence,
   then the complete build. Module 4 will replace the last step with a gate.
4. Make the report include commands, exit status, relevant output and any
   layer that was not exercised.
5. Demonstrate that the skill fails when its chosen test is intentionally
   given an impossible expectation. Revert that temporary change immediately.

For Culina, `./scripts/gate.sh` is the final gate. A focused skill should
still select the relevant GoogleTest and scenario before paying the full cost.

## Done when

- The skill reproduces the evidence from the morning's work.
- It fails clearly on a temporary negative control.
- It describes simulation as model evidence, not hardware validation.
