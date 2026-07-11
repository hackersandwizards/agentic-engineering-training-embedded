# Agentic Engineering for embedded systems

This is the two-day participant path for 15-16 July 2026, 09:00 to 16:50.
Culina is the shared engineering environment. The training content comes from
the Agentic Engineering one-pager; the C++ system gives every concept a concrete
task, constraint and feedback loop.

Participants start from the one-commit snapshot. It builds and runs one scenario
but contains no agent instructions, rules, skills, custom agents, plugins, hooks,
tests, sanitizers, CI or quality gate. The group adds each artifact after seeing
the problem it solves.

## Module 1: fundamentals and context engineering

| Time | Activity | Exercise or format | Result |
| --- | --- | --- | --- |
| 09:00 | Welcome, LLM vs agent, agent loop and tools | trainer-led | Shared mental model and evidence boundary |
| 09:35 | First contact and context audit | `m1-01` | Green baseline and measured fresh-session context |
| 10:10 | Break | | |
| 10:20 | Repository guidance and scoped rules | `m1-02`, `m2-01` | Minimal instructions with one scoped rule |
| 11:10 | Priming and compaction | `m1-04` | First custom skill and a clean handoff to fresh context |
| 11:40 | First agent-built change and test foundation | `m1-06` | Observable feature, GoogleTest, sanitizer preset and one trusted suite |
| 12:30 | Lunch | | |

## Module 2: advanced agent patterns

| Time | Activity | Exercise or format | Result |
| --- | --- | --- | --- |
| 13:15 | IDE integration and model selection | `m2-06` | Working IDE feedback loop and model decision record |
| 13:40 | Verification skill | `m2-02` | Second custom skill |
| 14:10 | Focused custom agents | `m2-03` | Two read-only reviewers with isolated concerns |
| 14:40 | Break | | |
| 14:50 | MCP connection and context-cost audit | `m2-05` | One useful external integration |
| 15:15 | Hooks, plugins and marketplace | `m2-07` | Observable hook and shareable plugin |
| 15:55 | Agent patterns and failure modes | trainer-led | Boundaries for context, permissions and deterministic code |
| 16:20 | Day-one retro | trainer-led | Artifact inventory and open questions |

## Module 3: practice transfer with RPI

| Time | Activity | Exercise or format | Result |
| --- | --- | --- | --- |
| 09:00 | Formalize Research-Plan-Implement | trainer-led | Explicit three-context sequence |
| 09:20 | Feature research | `m1-05` | Evidence-linked research report |
| 10:05 | Break | | |
| 10:15 | Plan and peer review | `m1-05` | Decision-complete approved plan |
| 11:05 | Group implementation | `m3-01` | Bounded vertical feature |
| 12:30 | Lunch | | |
| 13:15 | Finish, focused review and verification | `m3-01`, `m2-03`, `m2-02` | Reviewed diff and focused evidence |

## Module 4: Agentic SDLC and factory

| Time | Activity | Exercise or format | Result |
| --- | --- | --- | --- |
| 14:00 | Agents across the SDLC | `m4-04` | Refinement-to-review loop |
| 14:30 | Break | | |
| 14:40 | Harness, hooks and quality gates | `m4-01`, `m4-02` | Local and CI feedback loops |
| 15:30 | Scheduled agents and PR babysitting | `m4-04` | Bounded operational design |
| 16:00 | Starter kit and team transfer | `m4-03` | Team-ready artifact bundle and two-week trial |
| 16:35 | Group reports | trainer-led | Evidence, limitations and next use |
| 16:47 | Close | trainer-led | Commitments and follow-up |

## One-pager coverage

| Curriculum promise | Where participants practice it |
| --- | --- |
| LLM, agent loop and core tools | Welcome and `m1-01` |
| Context architecture, window, priming and compaction | `m1-01`, `m1-02`, `m1-04` |
| First feature built with an agent | `m1-06` |
| Model selection and IDE integration | `m2-06` |
| Rules, two skills and custom agents | `m2-01`, `m1-04`, `m2-02`, `m2-03` |
| MCP, hooks, plugins and marketplace | `m2-05`, `m2-07`, `m4-01` |
| Research-Plan-Implement | `m1-05`, `m3-01` |
| Refinement, planning, implementation and review | `m4-04` |
| Harness, factory loops, quality gates and fitness functions | `m4-01`, `m4-02`, `m4-04` |
| Starter kit and daily-work transfer | `m4-03` |

## Working agreement

- Keep one green, observable path through the system.
- Research, plan and implement in separate contexts.
- Check repository evidence before accepting a plausible claim.
- Run the narrow feedback loop before the full gate.
- Treat simulation as evidence about the model, not physical hardware.
- Keep human approval outside files and checks an agent can edit.
- Build artifacts from observed friction. Remove any artifact without a use case.
- Do not use Git history as an answer source.
