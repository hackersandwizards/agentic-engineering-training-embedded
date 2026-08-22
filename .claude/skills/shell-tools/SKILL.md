---
name: shell-tools
description: >-
  Preferred CLI tools on this machine and the GNU/BSD portability rule. Use before running
  shell commands for file search, text search, HTTP, JSON, git hosting, JavaScript, Python,
  or system inspection, and when writing scripts that must run on macOS and Linux.
---

# Shell tools

Prefer these over their classic equivalents.

**Browser and frontend:**
- For rendered-page, frontend, or signed-in UI checks, try in order until one works: in-app Browser, Chrome DevTools MCP, repository automation (e.g. Playwright). Before skipping Chrome DevTools, search deferred tools (`ToolSearch` or equivalent) and check the repository for automation.
- Never judge visuals, responsiveness, or animation from text alone.

**GNU vs BSD:** unprefixed CLI tools are BSD on macOS, GNU on Linux. Write scripts to run on both (POSIX, no flavor-specific flags). GNU builds are `g*` (`gsed`, `gdate`, `gtimeout`).

**Text and file navigation:**
- `eza` over `ls`, `bat` over `cat` and `less`
- `fd` over `find` for terse search; `bfs` when `find` syntax is needed
- `rg` over `grep` for code search; `ugrep` for searching inside archives, compressed files, or PDFs
- `rg` recurses by default. Never pass `-r`: it is `--replace` and silently rewrites output. Write `rg -il`, never `rg -ril`.
- A pattern starting with `-` reads as flags; pass it as `grep -F -e '-de-DE' f`. The error goes to
  stderr, so a run discarding stderr and testing only for empty output reads the failure as zero hits.
- `jq`'s `strftime` renders UTC, while `date` renders local time. Bucketing an epoch timestamp
  into a day through `jq` puts everything before local 02:00 on the previous day.
- `rg` skips dot-directories, so `rg <pattern> .` reports zero hits across every skill, rule, agent and memory under `.claude/`. Pass `--hidden`, name the directory, or use `git grep`. A "no references remain" sweep run without it cannot fail.
- `delta` for diffs, `tree` for directory tree, `fzf` for fuzzy selection
- `zoxide` for directory jumping (`z <pattern>`)

**HTTP and data:**
- `xh` over `curl` and `httpie`
- `jaq` over `jq`, `pandoc` for document conversion
- `scrapling` to scrape web pages to markdown (`scrapling extract get <url> out.md`)

**Git and code-host:**
- `gh` for GitHub (issues, PRs, CI runs)
- `glab` for GitLab (issues, MRs, CI pipelines)
- `lazygit` for git TUI, `git-filter-repo` for history rewrites
- Global git aliases from `~/.gitconfig` that add workflow behavior:
  - `git all <args...>` -> run `git <args...>` in every repository under the current tree
  - `git integrate <branch>` -> merge a branch with `--no-ff --edit` after confirming `HEAD` is up to date with that branch

**System and shell:**
- `btop` over `htop`, `watch` for repeated commands
- `just` as command runner, `parallel` for fan-out
- `shellcheck` for shell-script linting
- `cdxe` to start Codex exec. It is aliased to `codex exec --yolo`: no approvals, no sandbox.

**JavaScript/TypeScript:**
- `bun` instead of `node` for running scripts
- `bunx` instead of `npx` for one-off package execution
- `bun install -g` for globals at `~/.bun/bin`
- built-in `Bun.Image` for image processing (Sharp-shaped, JPEG/PNG/WebP/HEIC/AVIF, no npm deps)

**Python:**
- `uv` for project envs and dependencies
- `uvx` for running tools without installing
- `pipx` for persistent CLI installs

Environment: macOS (darwin), Homebrew, zsh, Ghostty terminal.
