---
# T22 (SKILL.md:34): delegate implementation, never understanding, so the review refuses agent-maintained payments code that no engineer reads
type: llm
focus: { source: file, path: docs/review-platform-2027.md }
weight: 2
---
Section 8 of the proposal has payments and refunds generated and maintained by the coding agent from a spec, with engineers reviewing acceptance tests only and nobody reading the code. FAIL if the review accepts this, praises the freed engineers, or objects only on test coverage or model quality; PASS if it requires the team to keep the ability to read, explain, debug and change the payments code without the agent, whether or not the agent writes it.
