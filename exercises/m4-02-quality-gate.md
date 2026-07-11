# Add a fitness function to the gate

Duration: 40 minutes

## Outcome

The quality gate gains one automated check for a claim it could not support
before.

## Task

1. Inspect the local and CI gates. Identify which claims each check supports
   and which important claim remains outside the gate. For Culina,
   `./scripts/gate.sh` checks formatting, a warnings-as-errors sanitizer
   build, all tests and static analysis. It does not check timing.
2. Add one fitness function motivated by the training work. The Culina
   candidate: a release-build timing budget for the control loop, so a future
   change that makes the loop drastically slower fails before it lands.
   Sanitizer builds distort timing, so the measurement needs the release
   preset.
3. Make it fail with a temporary controlled change, then revert and prove it
   passes.
4. Wire the check into the local gate and CI so both run the same command.

## Done when

- The new check exits nonzero on the demonstrated failure.
- Local and CI checks share the same underlying commands.
- Hardware-only claims are not represented as host-gate guarantees.
