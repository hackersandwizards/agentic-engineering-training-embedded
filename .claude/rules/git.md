# Git

Name the paths on `git commit` itself, `--amend` included. Never `git add -A` or `git add .`, and
never a bare `git commit`: another session sharing this working tree may already hold entries in
the index, and a commit without a pathspec takes all of them. `git add` each new file by name, and
both paths of a `git mv`, before committing: a pathspec takes what is modified under it and skips
what is untracked, so naming a directory leaves a new file out while committing everything that
points at it, and naming only a rename's destination commits its add while its delete stays staged,
leaving the file at both paths. Either way the local gate still passes, because it reads the
working tree rather than the commit. Name files rather than the directory holding them: a directory
pathspec is no filter for whose work it is, and takes whatever another session has staged beneath
it.

A pathspec says which paths fold into `HEAD`, never whose commit `HEAD` still is. Verify that
before `--amend`, or another session's commit landing between your two is the one your work folds
into. Repair it index-free, `git commit-tree` plus `git update-ref` with the expected old value,
because `reset` and `rebase` destroy whatever a third session has staged. Abandon the repair if it
races: a wrong grouping over a correct tree is not worth rewriting commits other sessions are
already building on.

`git checkout --` and `git restore` read the same moving `HEAD`, so a revert of your own edit
installs whatever another session committed there since your run started, and destroys whatever a
third has uncommitted under the path. Read `HEAD` for those paths before reverting, and name the
paths there too.

Commit and push each finished batch without being asked: one coherent unit of work whose checks
pass, not each file and not a single commit at the end. Stay on the current branch; branch only
when the user asks.

`.git/index.lock` is another session committing, not stale state: deleting it corrupts the commit
already in flight. The pre-commit hook holds it for well over a minute, so retrying means a couple
of minutes of looping. Wait and retry; if it outlives that, name the owning process and report it
rather than clearing it.

A successful commit and a push that prints a ref update are not evidence the work landed. Read
`HEAD` back for those paths with `git ls-tree HEAD -- <paths>` before reporting anything committed.
`git commit <path>` answering `no changes added to commit` usually means another session already
swept your edit into its own commit, so find it with `git log -S` before editing again.

The author on a commit names the checkout a change ran in, never the hand that decided it. Every
session here commits under the machine's own git identity, agent runs included, and an agent commit
is marked only by its `Co-Authored-By` line. Take the date and the changed lines from `git log` and
attribute nothing to it: where provenance decides an escalation, the evidence is a message, a record
body or a run transcript, and the honest answer is often "unrecorded".

Everything happens in this working tree. Never create or enter a git worktree, and never give a
delegate `isolation: worktree`: every session shares this one checkout, a worktree branches from
`origin/main` rather than from what is already here, and whatever it leaves uncommitted shows up in
no other session and dies with the worktree.
