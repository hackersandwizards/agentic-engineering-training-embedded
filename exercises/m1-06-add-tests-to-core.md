# Ship the first small feature with a test

Duration: 50 minutes

## Outcome

The group ships its first observable change with an agent. One core component
also gains a deterministic test suite the group has demonstrated it can trust.

## Task

1. Extend the scenario language with `expect program == NAME`. It must report
   the active program name and support `none` while idle. Add one scenario that
   proves both states. This is the first agent-built feature.
2. Add the smallest test target and sanitizer-enabled development preset needed
   for deterministic host tests. Do not add CI or a repository gate yet.
3. Ask the agent to inventory core components against tests and rank the gaps.
   Read-only.
4. Pick one component. Good Culina candidates: `src/mcu/heater_pid` (output
   bounds, anti-windup), `src/mcu/interlocks` (lid open, overtemperature),
   `src/common/parse_number` (malformed and out-of-range input),
   `src/app/telemetry_store` (window queries, staleness).
5. Derive the expected behavior from the documents: the safety requirements,
   the protocol specification and the datasheets. A test copied from the
   implementation only proves the code agrees with itself.
6. Generate the tests, then review them. Reject assertion-free tests and tests
   that exercise a mock instead of the component.
7. Negative control: break the implementation once on purpose, prove the new
   tests fail, revert immediately.
8. Run the new scenario and focused suite under the sanitizers, then commit.

## Done when

- The new scenario passes for an active manual program and for `none` while idle.
- Each component test traces to a documented claim, not to the implementation.
- The suite failed on the negative control and is green after the revert.
- The focused tests pass under the sanitizer-enabled build.
