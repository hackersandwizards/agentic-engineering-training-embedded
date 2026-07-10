# Quality gate

Duration: 20 minutes

## Outcome

One command provides the repository's minimum evidence before a change lands.

## Task

1. Inspect the existing local and CI gates. Identify which claims each check
   supports and which important claim remains outside the gate.
2. Add or tighten one check motivated by today's feature.
3. Make it fail with a temporary controlled change, then revert and prove it
   passes.
4. Compare local and CI behavior so developers do not learn about avoidable
   failures only after pushing.

For Culina, start with `./scripts/gate.sh`. It checks formatting, a
warnings-as-errors sanitizer build, all tests, static analysis and the release
timing budget.

## Done when

- The command exits nonzero on the demonstrated failure.
- Local and CI checks share the same underlying commands.
- Hardware-only claims are not represented as host-gate guarantees.
