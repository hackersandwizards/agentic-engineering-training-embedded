# Close the IDE feedback loop

Duration: 35 minutes

## Outcome

The agent uses the team's IDE feedback where it improves the task, and the
group can choose a model from the work instead of from brand preference.

## Task

1. Connect the coding agent to IntelliJ, VS Code or the IDE available to the
   group. Use current official setup instructions.
2. Exercise selected-code context, diagnostics and diff review. Record which
   capabilities are native, MCP-provided or unavailable.
3. Run one safe symbol rename or compiler-error repair. Confirm both the agent
   and IDE observe the same final state.
4. Inventory any tools the IDE integration adds. Prefer the IDE operation only
   where it supplies semantic information the terminal operation lacks.
5. Choose models for research, implementation and fast mechanical work. Include
   Codex or an open-weight model when available. State the reason in terms of
   task complexity, feedback speed, cost or local-data requirements.
6. Remove broad auto-approval that the exercise did not need.

## Done when

- Selected context, diagnostics and diff review work or are marked unavailable.
- The model decision names the work each model performs.
- Tool permissions remain no broader than the demonstrated task.

