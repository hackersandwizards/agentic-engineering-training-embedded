# First contact and context audit

Duration: 40 minutes

## Outcome

You can explain how the agent gathered context, run one representative check
and measure the cost of the context loaded before useful work begins.

## Task

1. Before prompting, identify the agent loop you are about to use: instructions
   and context enter first, the model chooses tools, tool results return to the
   loop, and the agent reports or edits at the end.
2. Inspect the available tools and permission mode. Distinguish read, search,
   command and write capabilities.
3. Record the fresh-session context-window report supported by your agent. Include
   standing instructions, MCP tools and free capacity where the product exposes
   them. Do not optimize toward a universal percentage.
4. Ask the agent to orient itself without changing files. Require a concise
   architecture summary, main entry points, build command and verification
   options with file references.
5. Inspect which files and tools it chose. Challenge one unsupported claim and
   ask it to verify the claim from the repository.
6. Run the smallest meaningful build and the checked-in simulator smoke
   scenario. Capture the command, exit status and relevant output.
7. Identify one thing the agent could not establish from the repository, such
   as hardware behavior or an external requirement.
8. List what the repository itself is missing. Keep the list; later exercises
   must justify their artifacts against it.

The repository is a deliberately minimal core slice. Gaps you find are the
material for the next exercises, not oversights.

For Culina, use `cmake --preset dev`, build the `dev` preset and run one
scenario under `data/scenarios/checks/`.

## Done when

- The baseline is green.
- The architecture summary distinguishes application, safety controller,
  protocol and physical or simulated environment.
- Every important claim is either sourced or explicitly marked unknown.
- The context audit names what loads before the task and what earns that cost.
- The gap list names concrete files or components, not general wishes.
