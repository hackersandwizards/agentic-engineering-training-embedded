# Add documentation

Duration: 45 minutes

## Outcome

The repository has minimal, pointer-based agent guidance that measurably
improves a fresh session.

## Task

1. In a fresh session, run a baseline probe: ask the agent to build the
   project and run one check scenario. Note every wrong turn and every
   question it should not have needed to ask.
2. Generate a candidate guidance file with the mechanism your coding agent
   supports for repository-level instructions.
3. Curate it. Classify every line as universal, path-specific or on-demand.
   Replace copied protocol or safety content with pointers to
   `docs/c1link-protocol.md` and `docs/safety-requirements.md`. Delete
   anything a build or focused check can enforce more reliably.
4. Re-run the probe in a fresh session and compare against step 1.
5. Commit the guidance.

Do not optimize for a line count or context percentage. Optimize for correct
behavior, clear ownership and low maintenance cost.

## Done when

- The fresh-session probe improves against the baseline from step 1.
- Every instruction has one authoritative source; no spec content is copied
  into guidance.
- The guidance is committed and the build stays green.
