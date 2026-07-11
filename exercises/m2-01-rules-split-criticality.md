# Derive scoped rules from observed friction

Duration: 30 minutes

## Outcome

One repeated correction from the morning becomes concise, scoped repository
guidance.

## Task

1. Review the morning sessions and identify a correction the group made more
   than once while adding documentation and tests.
2. Decide whether the correction belongs in documentation, an executable gate
   or agent guidance. Prefer an executable check when possible.
3. If guidance is appropriate, scope it to the files where it matters and link
   to the authoritative source.
4. Test the rule in a fresh context with a small representative request.
5. Remove speculative rules that were not supported by observed work.

Useful Culina candidates include safety-requirement traceability for
`src/mcu/**`, protocol versioning for `src/protocol/**` and deterministic
evidence for `src/sim/**`.

## Done when

- The rule prevents a real repeated failure from the morning.
- It is scoped narrowly and has one clear source of truth.
- The rule does not claim to replace human review or an engineering standard.
