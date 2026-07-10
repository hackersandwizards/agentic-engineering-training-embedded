# Ground a claim in engineering sources

Duration: 15 minutes, trainer-led short version

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

The correct outcome can be full agreement. Do not invent a discrepancy to make
the exercise interesting.

## Done when

- The trace contains an authoritative source, implementation and test evidence.
- Uncertainty remains visible instead of being filled with assumptions.
