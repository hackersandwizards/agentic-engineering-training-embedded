# Git

Name the paths on `git commit` itself, `--amend` included. Never `git add -A` or `git add .`, and
never a bare `git commit`: another session sharing this working tree may already hold entries in
the index, and a commit without a pathspec takes all of them. Read `git status` before each
commit and name the files you left behind because another session owns them.

Commit and push each finished batch without being asked. A batch is one coherent unit of work
whose checks pass: what the user asked for, or one self-contained part of it when the work spans
several. Commit at that boundary, not per file and not once at the end of a long session. Work
that is mid-edit, failing a check, or waiting on a question you asked stays uncommitted.

Push to the current branch and stay on it. Create a branch only when the user asks for one.
