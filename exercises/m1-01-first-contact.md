# First contact

Duration: 30 minutes

## Outcome

You can explain the system boundary, run one representative check and show the
evidence your coding agent used.

## Task

1. Ask the agent to orient itself without changing files. Require a concise
   architecture summary, main entry points, build command and verification
   options with file references.
2. Inspect which files and tools it chose. Challenge one unsupported claim and
   ask it to verify the claim from the repository.
3. Run the smallest meaningful build and one representative test or simulator
   scenario. Capture the command, exit status and relevant output.
4. Identify one thing the agent could not establish from the repository, such
   as hardware behavior or an external requirement.

For Culina, use `cmake --preset dev`, build the `dev` preset and run one
scenario under `data/scenarios/checks/`.

## Done when

- The baseline is green.
- The architecture summary distinguishes application, safety controller,
  protocol and physical or simulated environment.
- Every important claim is either sourced or explicitly marked unknown.
