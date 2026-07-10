# Agentic engineering for embedded systems

Participant exercises for a one-day workshop from 09:00 to 16:50.

Work in the real repository assigned by the trainer. Culina is the fallback
when access, build time or hardware dependencies block useful work. It starts
from a complete green reference state. There are no planted defects and no
answers hidden in Git history.

## Agenda

| Time | Focus | Exercise |
| --- | --- | --- |
| 09:00 | Welcome, goals and working agreement | trainer-led |
| 09:20 | First contact and executable evidence | `m1-01` |
| 09:50 | Read-only context audit | `m1-02` |
| 10:15 | Ground a claim in engineering sources | `m1-03`, trainer-led |
| 10:30 | Break | |
| 10:40 | Feature research | `m1-05` |
| 11:20 | Feature plan and peer review | `m1-05` |
| 12:30 | Lunch | |
| 13:15 | Group feature implementation | `m3-01` |
| 14:45 | Break | |
| 15:00 | Focused review | `m2-03` |
| 15:25 | Verification evidence and repository gate | `m2-02` |
| 15:50 | Derive one reusable artifact | choose `m1-04`, `m2-01` or `m4-01` |
| 16:15 | Transfer to the team repository | `m4-03` |
| 16:35 | Three-minute group reports | trainer-led |
| 16:47 | Commitments and close | trainer-led |

The trainer will shorten or swap exercises based on the repository and group
pace. `m2-04` and `m4-02` are optional extensions after the session.

## Working agreement

- Start from a green build and keep it green.
- Research before planning and approve the plan before implementation.
- Use repository evidence, requirements and component documentation. Do not
  accept a plausible answer without checking its source.
- Verify the narrow claim first, then run the repository gate.
- A simulator is evidence about its model, not proof about physical hardware.
- Human approval stays outside files and checks the agent can modify itself.
- Do not use Git history as an answer source for the training task.
