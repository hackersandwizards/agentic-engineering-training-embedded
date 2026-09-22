---
name: engineering
description: >-
  How to build and change software here (docs over code, when to ask, what never to simplify, comments,
  silent-failure gates), before implementing a feature, refactoring, fixing a bug, reviewing a change or
  planning non-trivial repository work, never for content edits, prose or business records.
---

# Engineering

Architecture docs (CLAUDE.md, rules) outrank existing code where the two disagree. Given a clear
bug report, fix it; ask only where the requirement contradicts itself, names a missing artifact,
or has two defensible readings. Never simplify away input validation at a trust boundary, error
handling that prevents data loss, security measures, or accessibility basics.

- Cleanup, review and quality passes scan the whole working tree, not only the files this
  conversation touched. Another session's in-flight change sits beside today's work: read it for
  context and leave it to its author. An unstaged change you revert is gone from git for good.
- A parser answering "malformed" with the same value it gives "legitimately empty" turns a loud
  failure into a silent one. Put that gate at the parser, never at each consumer.
- Repairing a record that read as absent does not re-run the jobs that skipped it, and those jobs
  left no trace of the skip. Find the window between the corruption and the repair, then check the
  repaired records against their untouched siblings.
- Comment deletion is the default. Write one only for a fact the code cannot state: an ordering
  constraint, an external limit or quirk, a security rationale, the bug a guard exists for, or a
  cross-file contract nothing else records. Keep directive comments (shellcheck, eslint, noqa,
  pragma, shebang).
- Removing a collection, a skill or an agent also deletes the tests that named it. Port every
  deleted case whose subject still exists: no gate goes red when coverage disappears.
