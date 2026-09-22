# Git

Other sessions share this working tree and its index.

- Name the paths on `git commit` itself, `--amend` included. Never `git add -A`, `git add .` or a
  bare `git commit`: a commit without a pathspec takes whatever another session staged.
- `git add` each new file by name, and both paths of a `git mv`, before committing. A pathspec
  skips untracked files, and naming only a rename's destination leaves the file at both paths. The
  local gate still passes, because it reads the working tree rather than the commit.
- Name files, not the directory holding them. A file can still hold another session's uncommitted
  lines beside yours: read each path's own diff, commit the clean paths now, and leave a shared file
  until its other author has committed.
- Before `--amend`, verify that `HEAD` is still your commit. Repair a wrong fold index-free with
  `git commit-tree` plus `git update-ref` and the expected old value, never `reset` or `rebase`.
  Abandon the repair if it races.
- `git checkout -- <path>` and `git restore` install whatever another session staged there. Revert
  with `git show HEAD:<path> > <path>`, after reading `HEAD` for that path, since it moves while
  your run is open.
- Commit and push each finished batch without being asked: one coherent unit whose checks pass.
  Stay on the current branch unless the user asks for another.
- `.git/index.lock` is another session committing. The pre-commit hook holds it for over a minute:
  wait and retry, and if it outlives a couple of minutes, name the owning process and report it.
  Never delete it.
- Read `HEAD` back with `git ls-tree HEAD -- <paths>` before reporting anything committed. `git
  commit <path>` answering `no changes added to commit` usually means another session swept your
  edit into its own commit: find it with `git log -S` before editing again.
- The commit author is the machine's git identity for every session. An agent commit is marked only
  by its `Co-Authored-By` line, so git history never says who decided a change: that evidence is a
  message, a record body or a run transcript, and is often unrecorded.
- Never create or enter a git worktree, and never give a delegate `isolation: worktree`. A worktree
  branches from `origin/main` rather than from this tree, and what it leaves uncommitted dies with
  it.
