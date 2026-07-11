# Agentic engineering for embedded systems

Participant exercises for a two-day online training, 09:00 to 16:50 each day.

The group works in the Culina training snapshot: a deliberately minimal core
slice that builds green. Over two days the group adds documentation, tests,
skills, reviewers, hooks, gates and one vertical feature, and the repository
grows toward the public reference. There are no planted defects and no answers
hidden in Git history. Team repositories are the transfer target in the
closing exercise.

## Day 1: fundamentals, context and agent patterns

| Time | Focus | Exercise |
| --- | --- | --- |
| 09:00 | Welcome, working agreement, concept briefing | trainer-led |
| 09:30 | First contact with the minimal core slice | `m1-01` |
| 10:15 | Break | |
| 10:25 | Add documentation: author and curate agent guidance | `m1-02` |
| 11:10 | Ground a claim in engineering sources | `m1-03`, trainer-led |
| 11:30 | Add tests to the under-tested core | `m1-06` |
| 12:30 | Lunch | |
| 13:15 | Derive scoped rules from morning friction | `m2-01` |
| 13:45 | Build a verification skill | `m2-02` |
| 14:30 | Focused review board with sub-agents | `m2-03` |
| 15:00 | Break | |
| 15:10 | Connect one MCP server, plugins walkthrough | `m2-05` |
| 15:40 | Model selection in depth | trainer-led |
| 16:00 | Extend robustness coverage under sanitizers | `m2-04` |
| 16:40 | Day-1 retro against the starter-kit inventory in `m4-03` | trainer-led |

## Day 2: hands-on transfer and the agentic SDLC

| Time | Focus | Exercise |
| --- | --- | --- |
| 09:00 | RPI formalization and session hygiene demo | trainer-led |
| 09:20 | Feature research | `m1-05` |
| 10:15 | Break | |
| 10:25 | Feature plan and peer review | `m1-05` |
| 11:15 | Group feature implementation | `m3-01` |
| 12:30 | Lunch | |
| 13:15 | Finish implementation, focused review on the diff | `m3-01`, `m2-03` |
| 14:00 | Verification evidence and repository gate | `m2-02` reuse |
| 14:30 | Hooks with honest authority | `m4-01` |
| 15:00 | Break | |
| 15:10 | Add a fitness function to the quality gate | `m4-02` |
| 15:50 | Scheduled agents, PR babysitting, workflows | trainer-led demo |
| 16:10 | Starter kit assembly and team transfer | `m4-03` |
| 16:35 | Three-minute group reports | trainer-led |
| 16:47 | Commitments and close | trainer-led |

The trainer will shorten or swap exercises based on group pace. `m1-04` is an
optional extension after the training.

## Working agreement

- Start from a green build and keep it green.
- Add the missing evidence before the feature: documentation and tests first.
- Research before planning and approve the plan before implementation.
- Use repository evidence, requirements and component documentation. Do not
  accept a plausible answer without checking its source.
- Verify the narrow claim first, then run the repository gate.
- A simulator is evidence about its model, not proof about physical hardware.
- Human approval stays outside files and checks the agent can modify itself.
- Do not use Git history as an answer source for the training task.
