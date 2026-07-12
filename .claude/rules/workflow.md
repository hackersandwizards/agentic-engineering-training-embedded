# How to Work

**Research Before Writing:**
- Investigate before acting: understand the problem, the surrounding system, and what already exists.
- Use Grep/Glob to map the space. Read files end-to-end when you will edit them, plus immediate callers and tests.
- Check if existing utilities already solve the problem. Reuse beats new code.

**Plan Mode Default:**
- Enter plan mode for non-trivial tasks (3+ steps, architectural decisions, verification work).
- Plan at two levels: high-level (overall goals and flow), then task-level (specific files or features). Implement only after the user approves both levels.
- Before planning anything complex, list every source document, methodology file, and reference you intend to use. Wait for the user to add or remove items before producing the plan.
- Bundle clarifying questions into one AskUserQuestion call (see collaboration.md), don't drip them one at a time.
- When something goes sideways mid-execution, stop and re-plan.

**Iterative Work:**
- Identify the high-level structure or plan first, then iterate on each section one at a time.
- Get explicit sign-off on each section before continuing to the next.
- Expect multiple review rounds. Do not push for premature closure.
- **Cleanup/review/quality-pass tasks: scan the whole working tree** (`git status` + `git diff`), not only files touched in the current conversation. In-flight changes from earlier sessions sit alongside today's work; reviewing only today's diff misses the drift that's the point of the review.

**Conform Before Creating:**
- Before adding new code, find 2-3 examples of similar code in the codebase. Match their naming, file structure, error handling, and test style.
- **Priority:** architecture docs (CLAUDE.md, rules) outrank existing code. Documented intent wins when current code contradicts it.
- Without a target doc, follow established codebase conventions. Consistency beats personal preference.

**One Feature at a Time:**
- Finish one well-defined feature before the next.
- Defer nice-to-haves until the core is complete and verified.
- **Completion Chain:** tests pass -> integration works end-to-end -> `/simplify` -> `/code-review high`. Run `/simplify` before the final summary on any task touching 3+ files or refactoring a non-trivial module. For auth/data/billing/external-API changes, add security + performance checks against baseline.
- Fix broken links in the chain before moving on.

**Git (trunk-based):** Commit and push to `main` directly, no feature branch. This overrides the harness "branch first" default. Branch only on request, and commit or push only when asked.

**When Stuck (STOP -> INVESTIGATE -> SIMPLIFY -> CLARIFY -> SEARCH):**
1. **STOP**: more code won't fix it. Re-plan.
2. **INVESTIGATE**: use a debugger, add logging, inspect actual I/O.
3. **SIMPLIFY**: isolate the problem with a smaller test.
4. **CLARIFY**: ask before guessing at requirements.
5. **SEARCH**: look for existing solutions in this codebase or elsewhere.

After 3 distinct investigation attempts without progress, escalate with: goal, attempts, actual vs expected, environment state, next steps needed.

**Autonomous Bug Fixing:**
- Given a clear bug report: fix it. Errors, logs, failing tests point the way.
- Fix failing CI without waiting to be told how.
- Ask for clarification when the requirement contradicts itself, references a missing artifact, or has more than one defensible interpretation. Otherwise proceed.

**Catch-yourself Cues** (when you notice the thought, redirect with the action):
- "Let me mock this" -> verify real integration first.
- "I'll assume this API works" -> test actual behavior.
- "This should be good enough" -> reach the quality bar.
- "Skip tests for now" -> write the test first.
- "Let me add this nice-to-have" -> finish the core feature.
- "This needs a clever solution" -> simple and clear beats clever.
- "This fix feels hacky" -> pause and ask: what's the elegant solution given everything you now know?
- Writing 20+ lines without running a test -> break and verify.
- Elaborate abstractions before core integration -> prove the happy path first.
- Multiple features in flight -> finish one, then move.
