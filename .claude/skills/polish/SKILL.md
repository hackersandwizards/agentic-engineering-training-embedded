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

Do not use the Workflow tool. It is too heavy for a polish. Fan out with direct subagents via the Agent tool only.

## 1. Preflight

Require a git repo. If not in one, stop and say so.

Run `git status`. If the working tree is dirty, stop and report the dirty files. Polish only commits its own changes. The user must commit or stash first.

Note the current branch for the push in phase 6.

## 2. Comment sweep

List source files with `git ls-files`, filtered to code extensions (sh, py, ts, js, tsx, jsx, go, rs, rb, java, kt, swift, c, h, cpp, sql, css, html, yaml, yml, toml). Skip vendored and generated paths (node_modules, dist, build, vendor, lockfiles).

Fan out subagents, one per directory batch, at most 4 in parallel. Each agent edits its batch by these rules:

- Delete comments that restate what the code does, name where code came from, or explain why a change is correct. The code already says it.
- Keep comments that state a non-obvious why or a constraint the code can't express. Tighten them to one short sentence.
- Keep public API docstrings, license headers, and directive comments (shellcheck, eslint, noqa, pragma, shebang).
- Rewritten comments use plain ASCII. No em-dashes, no en-dashes, no arrows, no ellipsis character, no curly quotes, no bullets. Short sentences. Why, not what.

Read each agent's report and spot-check one file per batch.

## 3. Quality, performance, security review

Fan out subagents, one per module or top-level directory, at most 4 in parallel. Each agent reviews against this checklist and reports findings with file:line.

- Minimalism: dead code, unused files, abstractions with one implementation, config for values that never change, code that reinvents the stdlib or an installed dependency.
- Design red flags: shallow modules, pass-through methods, repetition, vague names, nonobvious code.
- Performance: work inside loops that belongs outside, repeated I/O that could be batched, obvious quadratic passes over data that can grow.
- Security: missing input validation at trust boundaries, secrets in code, injection via string-built commands or queries, world-readable sensitive files.

Verify each finding yourself before fixing it. Apply the fixes. Skip findings that would add speculative structure.

## 4. Gates

Run the /simplify skill on the accumulated diff. Apply its fixes.

Run /code-review high. Fix confirmed findings.

Repeat both until each returns clean or only findings you have verified as false positives. Name any dismissed finding and the reason in the final summary.

## 5. Verify

Run the repo's own checks if present, in this order of discovery: justfile targets, package.json scripts (test, lint, build), Makefile, pytest, cargo test, go test.

A failing check blocks the commit. Fix the failure or, if it predates the sweep, report it and stop.

## 6. Commit and push

One commit. Message: one line summarizing the sweep, then a short body listing the areas touched.

Push to the branch noted in phase 1. If the push fails (no remote, auth, protected branch), report the error and stop.

## Notes

The sweep is idempotent. The first run on a repo is big, later runs are cheap.

When a rule here fights clarity, clarity wins.
