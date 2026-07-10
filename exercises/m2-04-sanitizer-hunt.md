# Extend robustness coverage

Duration: 30 minutes, optional

## Outcome

A host-side parser or command boundary has stronger negative-input coverage and
remains clean under sanitizers.

## Task

1. Choose a parser, decoder or CLI boundary used by the feature.
2. Identify malformed, truncated, overflowing and out-of-range inputs not yet
   represented in tests.
3. Add deterministic regression cases without assuming a crash already exists.
4. Run them under the sanitizer-enabled build.
5. If a defect appears, explain the report, fix the root cause and add the
   smallest permanent regression test.

For Culina, extend the `c1link_dump` tool tests or the command parser tests.
`data/captures/truncated.hex` is one existing malformed example.

## Done when

- The new cases have clear expected outcomes.
- Valid input still works.
- The sanitizer run is clean, whether or not a defect was discovered.
