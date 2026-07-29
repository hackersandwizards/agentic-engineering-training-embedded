---
name: engineering
description: >-
  How to approach building and changing software: research before writing, plan, TDD, the
  work/right/fast progression, documentation hierarchy, fail-fast validation, and what to do when
  stuck. Use before implementing a feature, refactoring, fixing a bug, reviewing a change, or
  planning non-trivial repository work. Skip for content edits, prose, and CRM data.
---

# Engineering

Readability and changeability are primary. Small functions, single responsibility. Reserve mocks
for isolated test seams.

## Research before writing

- Use Grep/Glob to map the space. Read files end-to-end when you will edit them, plus immediate
  callers and tests.

## Conform before creating

- Before adding new code, find 2-3 examples of similar code in the codebase. Match their naming,
  file structure, error handling, and test style.
- **Priority:** architecture docs (CLAUDE.md, rules) outrank existing code. Documented intent wins
  when current code contradicts it.
- Without a target doc, follow established codebase conventions. Consistency beats personal
  preference.

## Plan

- Enter plan mode for non-trivial tasks (3+ steps, architectural decisions, verification work).
- Plan at two levels: high-level (overall goals and flow), then task-level (specific files or
  features). Implement only after the user approves both levels.
- Before planning anything complex, list every source document, methodology file, and reference you
  intend to use. Wait for the user to add or remove items before producing the plan.
- When something goes sideways mid-execution, stop and re-plan.

## Test-driven development (default)

Follow RED-GREEN-REFACTOR for new features and non-trivial logic:

1. **RED**: write a concrete failing test that defines the requirement.
2. **GREEN**: write the minimum code to make it pass.
3. **REFACTOR**: clean up via `/simplify` and `/code-review high` while keeping tests green.

TDD applies to features and non-trivial logic in real projects. Scripts, spikes, one-off tools,
config tweaks, doc edits, typo fixes, and one-line changes skip the cycle and get the minimal
runnable check instead. Use judgment.

## Progression

1. **Make it work**: functioning code that passes tests.
2. **Make it right**: refactor for clarity and maintainability.
3. **Make it fast**: optimize only after profiling reveals a real bottleneck.

## One feature at a time

- Finish one well-defined feature before the next. Defer nice-to-haves until the core is complete
  and verified.
- **Completion chain:** tests pass -> integration works end-to-end -> `/simplify` ->
  `/code-review high`. Run `/simplify` before the final summary on any task touching 3+ files or
  refactoring a non-trivial module. For auth/data/billing/external-API changes, add security and
  performance checks against baseline.
- Fix broken links in the chain before moving on.
- **Cleanup, review, and quality passes scan the whole working tree** (`git status` + `git diff`),
  not only files touched in the current conversation. In-flight changes from earlier sessions sit
  alongside today's work.

## Fail fast and validate

- Validate aggressively at inputs and integration boundaries. Give clear, descriptive errors when
  something breaks.
- Actively probe edge cases, invalid inputs, and unexpected conditions.

## When not to be lazy

Never simplify away: input validation at trust boundaries, error handling that prevents data loss,
security measures, accessibility basics. Work that doesn't warrant full TDD still leaves one
runnable check behind: the smallest thing that fails if the logic breaks. Trivial one-liners need
no test. YAGNI applies to tests too.

## Comments and documentation

Match the file's existing comment density and idiom. Keep directive comments (shellcheck, eslint,
noqa, pragma, shebang).

Documentation hierarchy, in order of preference:

1. Working code: self-documenting through clear naming.
2. Tests: executable documentation; the tests are the spec.
3. README / docs: setup, architecture, API specs.
4. Comments: last resort, at the density of the surrounding code.

## Leave it better

- Leave it better than you found it, even when fixing something unrelated.
- Clean up test scripts, data files, temporary backups, and files from abandoned strategies when
  done.

## When stuck: STOP -> INVESTIGATE -> SIMPLIFY -> CLARIFY -> SEARCH

1. **STOP**: more code won't fix it. Re-plan.
2. **INVESTIGATE**: use a debugger, add logging, inspect actual I/O.
3. **SIMPLIFY**: isolate the problem with a smaller test.
4. **CLARIFY**: ask before guessing at requirements.
5. **SEARCH**: look for existing solutions in this codebase or elsewhere.

After 3 distinct investigation attempts without progress, escalate with: goal, attempts, actual vs
expected, environment state, next steps needed.

## Autonomous bug fixing

Given a clear bug report: fix it. Errors, logs, failing tests point the way. Fix failing CI without
waiting to be told how. Ask for clarification when the requirement contradicts itself, references a
missing artifact, or has more than one defensible interpretation. Otherwise proceed.
