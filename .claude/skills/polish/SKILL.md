---
name: polish
description: >-
  Full-repo quality pass. Sweeps every source file for comment hygiene and
  minimalism, reviews quality, performance, and security, runs /simplify and a
  second review over the resulting diff, then commits and pushes. Run when
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

The set moves both ways while you work: a new edit adds a file, and another session committing its
work drops one out. So re-derive it in phase 6 rather than assuming phase 1's list still holds.

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
`CLAUDE.md`. An instruction counts as code for this review. Look for a pointer to a path that no
longer exists, and a cap or boundary that contradicts an always-on rule. Look for one rule stated in
two files only within a single skill, or among the artifacts that are not skills. The same rule
carried by two different skills is not a finding: a skill is self-contained, and redundancy
between skills is the price of that. The defect there is the reverse, a skill pointing at a rule, an
agent, a memory file or another skill's file instead of stating the thing itself. Naming another
skill so the reader loads it is fine, as is naming the repository data and scripts the skill acts on.

Verify each finding yourself before fixing it. Apply the fixes. Skip findings that would add
speculative structure.

**A fix to a mirrored file goes into the hub copy, never this repo's.** The sync swaps the whole
directory, so a fix applied here is gone at the next run and no check catches it. Load
`agent-feedback` before you edit any instruction file: it decides which files are mirrors, and how
to sync one once you have changed it.

New failure modes learned during a run belong in `references/failure-modes.md`, not in this file.

## 4. Gates

Run the /simplify skill on the accumulated diff. Apply its fixes.

Then run phase 3 again over the accumulated diff rather than the tree: same fan-out, same `references/failure-modes.md`, same rule that you verify a finding before acting on it. `/code-review` refuses model invocation, so what runs is that procedure, never the command.

One pass of each. A second full round is the caller's call. Name any finding you dismissed, and why, in the final summary.

## 5. Verify

Run the repo's own checks if present, in this order of discovery: a `check`-named script or justfile target, then package.json scripts (test, lint, build), Makefile, pytest, cargo test, go test. Prefer the one-shot over the watcher: `test` is often `vitest`, which never exits.

Read "A gate that ran but was never read" in `references/failure-modes.md` before you run it. That section is passed to the phase 2-4 subagents and never to you, and both traps in it are this phase's: a piped gate reports the last command's exit status, and a commit whose paths the pre-commit hook does not route runs no gate at all. Run the gate on its own line and read `$?`.

A failing check blocks the commit. Fix it if the sweep caused it; report it and stop if it predates the sweep. A failure traced to a file in the exclusion set is another session's half-finished edit: wait for the gate to clear, and report it and stop if it does not. Never edit that file, and never bypass the hook, to get past it.

## 6. Commit and push

Re-run `git status` and drop any file that became dirty since phase 1 without an edit of yours. Name the remaining files this run edited as the `git commit` pathspec: never `git add -A` and never a bare `git commit`, or another session's staged work lands in your commit.

One commit. Message: one line summarizing the sweep, then a short body listing the areas touched.

Push to the branch noted in phase 1. If the push fails (no remote, auth, protected branch), report the error and stop.
