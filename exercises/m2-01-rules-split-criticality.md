# Derive scoped rules from observed friction

Duration: 20 minutes

## Outcome

One repeated correction from today's work becomes concise, scoped repository
guidance.

## Task

1. Review the feature session and identify a correction the team made more than
   once.
2. Decide whether the correction belongs in documentation, an executable gate
   or agent guidance. Prefer an executable check when possible.
3. If guidance is appropriate, scope it to the files where it matters and link
   to the authoritative source.
4. Test the rule in a fresh context with a small representative request.
5. Remove speculative rules that were not supported by today's work.

Useful Culina candidates include safety-requirement traceability for
`src/mcu/**`, protocol versioning for `src/protocol/**` and deterministic
evidence for `src/sim/**`.

## Done when

- The rule prevents a real repeated failure from today.
- It is scoped narrowly and has one clear source of truth.
- The rule does not claim to replace human review or an engineering standard.
