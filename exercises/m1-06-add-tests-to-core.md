# Add tests to the core

Duration: 60 minutes

## Outcome

One core component gains a deterministic test suite the group has demonstrated
it can trust.

## Task

1. Ask the agent to inventory core components against existing tests and rank
   the gaps. Read-only.
2. Pick one component. Good Culina candidates: `src/mcu/heater_pid` (output
   bounds, anti-windup), `src/mcu/interlocks` (lid open, overtemperature),
   `src/common/parse_number` (malformed and out-of-range input),
   `src/app/telemetry_store` (window queries, staleness).
3. Derive the expected behavior from the documents: the safety requirements,
   the protocol specification and the datasheets. A test copied from the
   implementation only proves the code agrees with itself.
4. Generate the tests, then review them. Reject assertion-free tests and tests
   that exercise a mock instead of the component.
5. Negative control: break the implementation once on purpose, prove the new
   tests fail, revert immediately.
6. Run the sanitizer build and commit.

## Done when

- Each test traces to a documented claim, not to the implementation.
- The suite failed on the negative control and is green after the revert.
- The repository gate passes with the new tests included.
