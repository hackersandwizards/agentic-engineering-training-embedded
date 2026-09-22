---
name: polish
description: >-
  Full-repo quality pass. Sweeps every source file for comment hygiene and
  minimalism, reviews quality, performance, and security, runs /simplify and a
  second review over the resulting diff, then commits and pushes. Run when
  the user asks to polish, clean up, or quality-pass the repo.
---

# Polish

Run the six phases in order. Stop only where a phase says so.

An argument narrows what each phase covers, never which phases run. Report what the scope excluded.

The argument also scopes where you hunt for defects, never which proven defects you may correct.
Once a fact is verified false, fix every live copy of it, the generator that produced them
included, in files the argument never named. The phase 1 exclusion set still binds: a file another
session is editing is reported as deferred whatever it contains.

Fan out with the Agent tool, never the Workflow tool.

## 1. Preflight

Run `git status` and record every file it reports as modified, staged, or untracked. That list is this run's exclusion set. A dirty tree does not stop the run: another session's work in progress is not yours to commit or stash.

Review and fix committed changes only. Never edit a file in the exclusion set: polish commits what it edits, and committing one would sweep in its author's uncommitted work. Report those files as deferred, for the next run once their author has committed.

Run the repo's own checks once and record the result: this baseline separates a pre-existing failure from one the sweep caused. A subagent reporting a red gate mid-run is usually reading another agent's half-finished edit.

## 2. Comment sweep

List source files with `git ls-files`, skip vendored and generated paths, and subtract the exclusion set before batching: the batch agents edit directly and never see phase 1.

Fan out one subagent per directory batch, told to read the Comments section of `references/failure-modes.md` and to change comments only. Spot-check one file per batch.

## 3. Quality, performance, security review

Fan out one subagent per module or top-level directory to review it for minimalism, design, performance and security, with the path of `references/failure-modes.md` in its prompt to read in full. Reviewers report and do not edit.

Review the instruction artifacts as their own module: `.claude/` rules, agents, and skills, plus `CLAUDE.md`. Look for a pointer to a path that no longer exists, a cap or boundary that contradicts an always-on rule, one rule stated twice inside a single skill or among the artifacts that are not skills, and any skill pointing outside its own directory at another skill, rule, agent or memory file by link or by name.

Verify each finding yourself before fixing it. Skip findings that would add speculative structure.

**A fix to a mirrored file goes into the hub copy, never the mirror.** The sync swaps the whole directory, so a fix applied to the mirror is gone at the next run and no check catches it. The sync script lists what is mirrored: edit and commit in the hub, then run it, and read its output rather than its exit status. The sync first commits every dirty hub path and fans it out, so read the hub's `git status --porcelain` before running it. A dirty path this run did not write defers the sync: copy the files this run committed from hub `HEAD` into this repository's mirror and report the other repositories as pending.

New failure modes learned during a run belong in `references/failure-modes.md`, not in this file.

## 4. Gates

Run the /simplify skill on the accumulated diff. Apply its fixes.

Then run phase 3 again over the accumulated diff rather than the tree. `/code-review` refuses model invocation, so what runs is that procedure, never the command.

One pass of each. Name any finding you dismissed, and why, in the final summary.

## 5. Verify

Run the repo's own checks. Prefer the one-shot over the watcher: `test` is often `vitest`, which never exits.

Run the gate on its own line and read `$?`. "A gate that ran but was never read" in `references/failure-modes.md` names this phase's two traps.

A failing check blocks the commit. Fix it if the sweep caused it; report it and stop if it predates the sweep. A failure traced to a file in the exclusion set is another session's half-finished edit: wait for the gate to clear, and report it and stop if it does not. Never edit that file, and never bypass the hook, to get past it.

## 6. Commit and push

Re-run `git status` and drop any file that became dirty since phase 1 without an edit of yours. Name the remaining files this run edited as the `git commit` pathspec.

Commit each coherent batch once it passes the gate.

Push to the branch you started on. If the push fails, report the error and stop.
