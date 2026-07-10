# Task-specific context package

Duration: 25 minutes, choose only if this solves friction observed today

## Outcome

You have a small, reusable way to load the right evidence for one recurring
task without expanding global repository instructions.

## Task

1. Pick one repeated context problem from today's feature work, such as protocol
   changes, control-loop changes or safety review.
2. Write a tool-supported command, prompt or skill that tells the agent which
   sources to inspect, which checks to run and what evidence to report.
3. Use pointers instead of copying source content into the package.
4. Test it in a fresh session with a concrete domain question.
5. Remove every step that did not improve the answer or verification.

For Culina, a protocol context package should load the C1-Link specification,
framing implementation and parser tests. A safety package should load the
safety requirements, interlocks and traceability tests.

## Done when

- The package is task-specific and works in a fresh session.
- Its report states what was inspected, what was run and what remains unknown.
- The concept survives if the team changes coding-agent products.
