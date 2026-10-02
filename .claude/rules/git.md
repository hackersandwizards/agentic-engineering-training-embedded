# Git

Other sessions share this working tree and its index.

- Name the paths on `git commit` itself, `--amend` included. Never `git add -A`, `git add .` or a
  bare `git commit`: a commit without a pathspec takes whatever another session staged.
- Commit a path holding `[` or `*` with `:(literal)<path>`, never `git --literal-pathspecs`, which
  exports `GIT_LITERAL_PATHSPECS=1` into the hook, so every pathspec the hook passes to git turns
  literal.
- `git add` each new file by name, and both paths of a `git mv`, before committing. A pathspec
  skips untracked files, and naming only a rename's destination leaves the file at both paths. The
  local gate still passes, because it reads the working tree rather than the commit.
- A case-only rename commits nothing through a pathspec where `core.ignorecase` is true: the commit
  reports success and leaves the rename staged. Rename through an intermediate name in two commits
  (`Foo` -> `foo-case` -> `foo`) and read `git ls-tree HEAD -- <dir>` afterwards.
- Name files, not the directory holding them. A file can still hold another session's uncommitted
  lines beside yours: read each path's own diff, commit the clean paths now, and leave a shared file
  while its other author's session is open.
- Before `--amend`, verify that `HEAD` is still your commit. Repair a wrong fold index-free with
  `git commit-tree` plus `git update-ref` and the expected old value, never `reset` or `rebase`.
  Abandon the repair if it races.
- `git checkout -- <path>` and `git restore` install whatever another session staged there. Revert
  with `git show HEAD:<path> > <path>`, after reading `HEAD` for that path, since it moves while
  your run is open.
- Commit and push each finished batch without being asked: one coherent unit whose checks pass.
  Stay on the current branch unless the user asks for another.
- Before any work in a repository, commit, `git fetch`, `git merge origin/<default branch>`, and
  push, never `git pull`. A read-only run only fetches and reads `origin/<default branch>` with
  `git show`. Where `pgrep -x claude`, which skips your own session, finds no process whose
  `lsof -a -d cwd -p <pid>` is this repository, commit every change while the gate passes.
  Otherwise commit only your own, never stash, and ask the person in plain words only where another
  session's file blocks the merge. In a conflict keep both sides' additions, the later change
  winning where they contradict. A rejected push repeats the update. Where the merge fails, read
  each record you act on from `origin/<default branch>` with `git show`. Where the fetch fails, act
  on nothing outside the repository, such as mail, Qonto or the calendar, and say why.
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
