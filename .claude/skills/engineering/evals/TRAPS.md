# Traps in SKILL.md

Codes: M = mechanism (repository-learned, the eval must show the skill is needed), G = generic
(procedure a capable model runs anyway, the eval must show it passes without the skill), P = a
demand of the prompt itself. Line numbers are `SKILL.md` at 125 lines.

## Mechanism

| Code | Lines | Trap | Case |
|---|---|---|---|
| M1 | 65-68 | Cleanup passes scan the whole working tree; another session's in-flight changes are read and left to their author; an unstaged change you revert is gone for good | comment-cleanup-dirty-tree |
| M2 | 75-76 | A parser answering "malformed" with the value it gives "empty" turns a loud failure silent; the gate sits at the parser, never at each consumer | config-loader-malformed |
| M3 | 77-79 | Repairing a record read as absent does not re-run the jobs that skipped it; find the window between corruption and repair and check the affected records | config-loader-malformed |
| M4 | 90-93 | Comment deletion is the default; keep only a fact the code cannot state, plus directive comments | comment-cleanup-dirty-tree |
| M5 | 106-108 | Removing a collection, skill or agent deletes the tests that named it; port every case whose subject still exists, since no gate goes red on lost coverage | delete-reports-feature |

## Generic

| Code | Lines | Trap | Case |
|---|---|---|---|
| G1 | 12-13 | Readability, small functions, mocks only at seams | not covered |
| G2 | 17-18 | Grep/Glob first; read files end-to-end plus callers and tests | config-loader-malformed (Read of the caller), delete-reports-feature (format_money kept because invoices.py calls it) |
| G3 | 22-27 | Match 2-3 existing examples; docs outrank code | not covered |
| G4 | 31-36 | Plan mode, two planning levels, list sources, re-plan | not covered |
| G5 | 40-48 | Red-green-refactor, skipped for trivia | not covered directly |
| G6 | 52-54 | Work, right, fast | not covered |
| G7 | 58-64 | One feature at a time; completion chain ending in tests, `/simplify`, review | all three (tests run before finishing) |
| G8 | 72-74 | Validate at boundaries; probe edge cases | not covered |
| G9 | 83-86 | Never simplify away validation; leave one runnable check | config-loader-malformed (the new test asserts the raise) |
| G10 | 95-100 | Documentation hierarchy | not covered |
| G11 | 104-105 | Clean up temp files | not covered |
| G12 | 110-119 | Stuck ladder, escalate after 3 attempts | not covered |
| G13 | 123-125 | Fix a clear bug without asking; ask only on contradiction | config-loader-malformed (no question, data file repaired), delete-reports-feature (cli, its test and README cleaned) |

## Cases

- `comment-cleanup-dirty-tree`: M1, M4, G7, P. Prompt "Clean up the comments under ledger/ and commit." Fixture: noise, stale, directive and fact comments in `ledger/parse.py`; another author's unstaged edit to `ledger/totals.py` and untracked `ledger/export_csv.py`.
- `delete-reports-feature`: M5, G2, G7, G13, P. Prompt "Delete the reports feature." Fixture: `tests/test_reports.py` holds three `format_money` cases; `shop/invoices.py` still calls `format_money`.
- `config-loader-malformed`: M2, M3, G2, G7, G9, G13. Prompt "Fix the bug in the config loader and add a test." Fixture: `load_settings` returns `{}` on `JSONDecodeError` as on a missing file; `config/settings.json` carries a trailing comma since a commit dated four days ago; two consumers.

## Grading notes

- `file_exists` counts only files created during the run, so survival of a scaffold file is graded through its contents (`target: { source: file }`) and deletion through the `rm` call (`tool_used`) plus the `git status --short` the prompt asks for.
- `tool_used` graders with `min: 0, max: 0` carry `arm: both` so the no-plugin arm is scored on them too.
- `skill-fired.md` is an indicator only; the runner excludes `tool_used: Skill` from the score in a two-arm run.
- `git stash` is not banned: it is recoverable and the skill does not name it.

## Not covered

- M1's first half, "scan the whole working tree, not only files touched in the conversation": in an eval every file is untouched by the conversation, so only the leave-to-author half is testable.
- M3's last clause, "check the repaired records against their untouched siblings": the fixture has no records to compare; the case grades the window and the statement that the fix does not undo the runs.
- G1, G3, G4, G6, G8, G10, G11, G12: G4 needs plan mode, absent from `allowed_tools`; G12 needs a stuck run, which a synthetic fixture cannot force without a flaky trap; the rest have no observable in these three tasks. A cut of any of them is unproven by this suite either way.
- G5 red-green-refactor order: `tool_order` could assert a test edit before the loader edit in `config-loader-malformed`; left out because the prompt says "add a test" and the order proves little.
