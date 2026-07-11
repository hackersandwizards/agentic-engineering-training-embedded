# Add a fitness function to the gate

Duration: 40 minutes

## Outcome

The repository gains a local and CI quality gate, including one fitness
function for a claim the normal build cannot support.

## Task

1. Assemble the checks built during the training into one local command:
   formatting, warnings-as-errors sanitizer build, tests and static analysis.
2. Add CI that calls the same underlying commands instead of copying a second
   definition of the gate.
3. Identify which claims the gate supports and which remain outside it.
4. Add one fitness function motivated by the training work. The Culina
   candidate: a release-build timing budget for the control loop, so a future
   change that makes the loop drastically slower fails before it lands.
   Sanitizer builds distort timing, so the measurement needs the release
   preset.
5. Make it fail with a temporary controlled change, then revert and prove it
   passes.
6. Run the gate locally and inspect the CI definition.

## Done when

- The new check exits nonzero on the demonstrated failure.
- Local and CI use one gate definition.
- Hardware-only claims are not represented as host-gate guarantees.
