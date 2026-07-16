# Subagents

- Delegate when: (a) a task spans 3+ files, (b) research could fill the main context, (c) multiple independent queries can run in parallel.
- One task per subagent for focused execution.
- Fan out at most 3 subagents at a time; ask before spawning more. Applies doubly in ultra mode, where every extra agent chews quota.
- Before building or changing Claude Code artifacts (skills, rules, subagents, hooks, output styles, settings, MCP), consult the `claude-code-guide` agent or official docs. Don't guess the frontmatter or mechanics from memory.

# Tooling preferences

Modern CLI replacements installed via Homebrew. Prefer when running shell commands.

**Browser and frontend:**
- Browser automation priority among available options (highest to lowest): OpenAI's in-app Browser, Chrome DevTools MCP, project-local browser automation such as Playwright. Applies to rendered-page inspection, frontend QA, and signed-in UI interaction.
- Never judge visual design, responsive behavior, or animation from a text crawl alone.

**GNU vs BSD:** unprefixed CLI tools are BSD on macOS, GNU on Linux. Write scripts to run on both (POSIX, no flavor-specific flags). GNU builds are `g*` (`gsed`, `gdate`, `gtimeout`).

**Text and file navigation:**
- `eza` over `ls`, `bat` over `cat` and `less`
- `fd` over `find` for terse search; `bfs` when `find` syntax is needed (POSIX-compatible, faster traversal)
- `rg` over `grep` for code search; `ugrep` for searching inside archives, compressed files, or PDFs
- `rg -r` is `--replace` (rewrites output), not recursive
- `delta` for diffs, `tree` for directory tree, `fzf` for fuzzy selection
- `zoxide` for directory jumping (`z <pattern>`)

**HTTP and data:**
- `xh` over `curl` and `httpie`
- `jaq` over `jq` (Rust port, faster), `pandoc` for document conversion
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
- `cdxe` to start Codex exec (`codex exec`)

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
