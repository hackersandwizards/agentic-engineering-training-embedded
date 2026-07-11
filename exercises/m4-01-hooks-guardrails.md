# Turn hook events into feedback

Duration: 30 minutes

## Outcome

The day-one hook becomes a useful feedback loop without pretending to be a
security or approval boundary.

## Task

1. Review the events captured by the day-one hook. Identify one repeated or
   expensive failure that deserves automatic feedback.
2. Extend the hook only enough to run a focused check, record structured output
   or notify a developer when the full gate finishes.
3. Test success, failure and malformed hook input.
4. Document who can change the hook, where its output goes and what it cannot
   guarantee.

Do not store human approval in a file inside the working tree. An agent that can
edit the protected source can usually edit that file or the hook as well. Code
owners, protected branches, CI environments and human review are external
controls; local hooks are developer feedback.

## Done when

- The hook addresses a problem observed during the training.
- Failure explains the next action.
- The group can state its trust boundary in one sentence.
