# Git

Name the paths on `git commit` itself, `--amend` included. Never `git add -A` or `git add .`, and
never a bare `git commit`: another session sharing this working tree may already hold entries in
the index, and a commit without a pathspec takes all of them. `git add` each new file by name, and
both paths of a `git mv`, before committing: a pathspec takes what is modified under it and skips
what is untracked, so naming a directory leaves a new file out while committing everything that
points at it, and naming only a rename's destination commits its add while its delete stays staged,
leaving the file at both paths. Either way the local gate still passes, because it reads the
working tree rather than the commit.

A pathspec says which paths fold into `HEAD`, never whose commit `HEAD` still is. Verify that
before `--amend`, or another session's commit landing between your two is the one your work folds
into. Repair it index-free, `git commit-tree` plus `git update-ref` with the expected old value,
because `reset` and `rebase` destroy whatever a third session has staged. Abandon the repair if it
races: a wrong grouping over a correct tree is not worth rewriting commits other sessions are
already building on.

Commit and push each finished batch without being asked: one coherent unit of work whose checks
pass, not each file and not a single commit at the end. Stay on the current branch; branch only
when the user asks.

`.git/index.lock` is another session committing, not stale state: deleting it corrupts the commit
already in flight. Wait and retry; if it outlives several retries, report it rather than clearing it.

Everything happens in this working tree. Never create or enter a git worktree, and never give a
delegate `isolation: worktree`: every session shares this one checkout, a worktree branches from
`origin/main` rather than from what is already here, and whatever it leaves uncommitted shows up in
no other session and dies with the worktree.
