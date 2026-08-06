---
name: polish
description: >-
  Full-repo quality pass. Sweeps every source file for comment hygiene and
  minimalism, reviews quality, performance, and security, runs /simplify and
  /code-review high on the resulting diff, then commits and pushes. Run when
  the user asks to polish, clean up, or quality-pass the repo.
---

# Polish

Run all six phases in order. Do not skip a phase. Do not stop between phases unless a phase says so.

An argument narrows what each phase covers, never which phases run. Scoped to one area, phase 2
still sweeps the code changed alongside it; report what the scope excluded rather than dropping
the phase.

Do not use the Workflow tool. Fan out with direct subagents via the Agent tool only.

## 1. Preflight

Require a git repo. If not in one, stop and say so.

Run `git status` and record every file it reports as modified, staged, or untracked. That list is this run's exclusion set. A dirty tree does not stop the run: another session's work in progress is not yours to commit or stash.

Review and fix committed changes only. Never edit a file in the exclusion set: polish commits what it edits, and committing one would sweep in its author's uncommitted work. Report those files as deferred, for the next run once their author has committed.

The set only grows while you work, so re-derive it in phase 6.

Run the repo's own checks once and record the result. Phase 5 needs this baseline to separate a pre-existing failure from one the sweep caused, and a subagent reporting a red gate mid-run is usually reading another agent's half-finished edit.

Note the current branch for the push in phase 6.

## 2. Comment sweep

List source files with `git ls-files`, filtered to code extensions (sh, py, ts, js, tsx, jsx, go, rs, rb, java, kt, swift, c, h, cpp, sql, css, html, yaml, yml, toml). Skip vendored and generated paths (node_modules, dist, build, vendor, lockfiles), and subtract the exclusion set before batching: these agents edit directly and never see phase 1.

Fan out subagents, one per directory batch. Tell each agent to read the Comments section of
`references/failure-modes.md` and edit its batch by it, and to change comments only.

Read each agent's report and spot-check one file per batch.

## 3. Quality, performance, security review

Fan out subagents, one per module or top-level directory. Each agent reviews its module for
minimalism, design, performance and security, and reads `references/failure-modes.md` in full for
the defects a competent review misses. Pass that path in every agent's prompt. Reviewers report;
they do not edit.

Review the instruction artifacts as their own module: `.claude/` rules, agents, and skills, plus
`CLAUDE.md`. `minimalism.md` counts an instruction as code. Look for one rule stated in two files,
a pointer to a path that no longer exists, and a cap or boundary that contradicts an always-on rule.

Verify each finding yourself before fixing it. Apply the fixes. Skip findings that would add
speculative structure.

New failure modes learned during a run belong in `references/failure-modes.md`, not in this file.

## 4. Gates

Run the /simplify skill on the accumulated diff. Apply its fixes.

Run /code-review high. Fix confirmed findings.

Repeat both until each returns clean or only findings you have verified as false positives. Name any dismissed finding and the reason in the final summary.

## 5. Verify

Run the repo's own checks if present, in this order of discovery: a `check`-named script or justfile target, then package.json scripts (test, lint, build), Makefile, pytest, cargo test, go test. Prefer the one-shot over the watcher: `test` is often `vitest`, which never exits.

A failing check blocks the commit. Fix the failure or, if it predates the sweep, report it and stop.

## 6. Commit and push

Re-run `git status` and drop any file that became dirty since phase 1 without an edit of yours. Name the remaining files this run edited as the `git commit` pathspec; `git.md` owns that rule.

One commit. Message: one line summarizing the sweep, then a short body listing the areas touched.

Push to the branch noted in phase 1. If the push fails (no remote, auth, protected branch), report the error and stop.
