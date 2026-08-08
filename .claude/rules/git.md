# Git

Name the paths on `git commit` itself, `--amend` included. Never `git add -A` or `git add .`, and
never a bare `git commit`: another session sharing this working tree may already hold entries in
the index, and a commit without a pathspec takes all of them.

Commit and push each finished batch without being asked: one coherent unit of work whose checks
pass, not each file and not a single commit at the end. Stay on the current branch; branch only
when the user asks.

Everything happens in this working tree. Never create or enter a git worktree, and never give a
delegate `isolation: worktree`: every session shares this one checkout, a worktree branches from
`origin/main` rather than from what is already here, and whatever it leaves uncommitted shows up in
no other session and dies with the worktree.
