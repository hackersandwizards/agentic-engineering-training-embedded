# Ground a claim in engineering sources

Duration: 20 minutes, trainer-led short version

## Outcome

You can distinguish a repository-backed conclusion from a plausible guess.

## Task

1. Choose one behavior governed by a protocol, requirement, component document
   or interface contract.
2. Ask the agent to trace it from source to implementation to verification.
3. Require file and line references, assumptions and missing evidence.
4. Classify every finding as confirmed, ambiguous or unsupported.
5. Decide the next evidence needed for ambiguous cases: a test, measurement,
   hardware run, requirement clarification or vendor document.

For Culina, trace one motor ramp limit from
`docs/datasheets/motor-driver-mx400.md`, or one safety requirement from
`docs/safety-requirements.md`.

On the minimal baseline the verification leg of a trace may not exist yet.
That is a finding, not a failure. Feed it into the add-tests exercise.

The correct outcome can be full agreement. Do not invent a discrepancy to make
the exercise interesting.

## Done when

- The trace names an authoritative source, the implementation and the test
  evidence, or records which of the three is missing.
- Uncertainty remains visible instead of being filled with assumptions.
