# Guardrails with honest authority

Duration: 30 minutes

## Outcome

One automation hook reduces a real workflow mistake without pretending to be a
security or approval boundary.

## Task

1. Choose an observed problem suited to a hook, such as reminding the agent to
   run focused tests after changing control logic or notifying a developer when
   a long gate finishes.
2. Check the current official documentation for your agent's hook schema.
3. Implement the smallest reversible hook and test both success and failure.
4. Document who can change the hook and what it cannot guarantee.

Do not store human approval in a file inside the working tree. An agent that can
edit the protected source can usually edit that file or the hook as well. Code
owners, protected branches, CI environments and human review are external
controls; local hooks are developer feedback.

## Done when

- The hook addresses a problem observed during the training.
- Failure explains the next action.
- The group can state its trust boundary in one sentence.
