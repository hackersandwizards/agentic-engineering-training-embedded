# Context audit

Duration: 25 minutes

## Outcome

The repository memory contains only guidance that is useful across tasks, with
pointers to details that should be loaded on demand.

## Task

1. Review the repository-level agent instructions, if they exist.
2. Classify each instruction as universal, path-specific, task-specific or
   redundant with an executable check.
3. Record which universal guidance should remain at the root, which path-specific
   guidance should be scoped, and which copied details should become links.
4. Record instructions that appear vague, stale or redundant with the build.
5. Do not change repository guidance yet. Keep the audit for the afternoon
   artifact decision.

Do not optimize for a line count or context percentage. Optimize for correct
behavior, clear ownership and low maintenance cost.

## Done when

- The audit classifies every standing instruction and cites concrete examples.
- It identifies authoritative sources and redundant copies.
- No repository guidance changed during the read-only exercise.
