# Traps in `shell-tools`

A trap is a line a capable model gets wrong without it (bait), one it would follow on its own
(guessable), a demand the prompt itself makes (prompt), or a preference with no surface in a
sandbox (not gradeable). Line numbers are `SKILL.md` at 62 lines; `agents/openai.yaml` holds no
rule. Cases: A = `flag-sweep-hidden-dirs`, B = `portable-release-script`,
C = `daily-buckets-local-time`. Every case builds its own repository in `fixture.sh` (git,
coreutils, python3, node; no environment) and names no company, client or record.

| ID | file:line | Trap | Kind | Case |
|---|---|---|---|---|
| T1 | SKILL.md:14 | Rendered-page checks: in-app Browser, then Chrome DevTools MCP, then repository automation; search deferred tools before skipping DevTools | not gradeable | none |
| T2 | SKILL.md:15 | Never judge visuals, responsiveness or animation from text | not gradeable | none |
| T3 | SKILL.md:17 | Unprefixed tools are BSD on macOS and GNU on Linux; a script that runs on both is POSIX with no flavor-specific flag; GNU builds are `g*` | bait | B (sed -i, date flags, checksum, long options, short flags), C (date flags) |
| T4 | SKILL.md:20 | `eza` over `ls`, `bat` over `cat` and `less` | not gradeable | none |
| T5 | SKILL.md:21 | `fd` over `find`, `bfs` for `find` syntax | not gradeable | none |
| T6 | SKILL.md:22 | `rg` over `grep`; `ugrep` inside archives, compressed files, PDFs | not gradeable | none |
| T7 | SKILL.md:23 | `rg -r` is `--replace` and rewrites the output; `rg -il`, never `rg -ril` | bait | A |
| T8 | SKILL.md:24 | A pattern starting with `-` reads as flags; pass it after `-e` or `--` | bait | A |
| T9 | SKILL.md:25 | The option error goes to stderr; discarding it and testing for empty output reads the failure as zero hits | bait | A |
| T10 | SKILL.md:26-27 | `jq`'s `strftime` renders UTC while `date` renders local time; bucketing epochs into days through it shifts everything before local 02:00 to the previous day | bait | C |
| T11 | SKILL.md:28 | `rg` skips dot-directories, so a sweep without `--hidden`, a named directory or `git grep` cannot fail on `.github/` and dotfiles | bait | A |
| T12 | SKILL.md:29 | `delta` for diffs, `tree`, `fzf` | bait (delta only) | B (runbook) |
| T13 | SKILL.md:30 | `zoxide` for directory jumping | not gradeable | none |
| T14 | SKILL.md:33 | `xh` over `curl` and `httpie` | bait | B (runbook) |
| T15 | SKILL.md:34 | `jaq` over `jq`, `pandoc` for document conversion | not gradeable | none |
| T16 | SKILL.md:35 | `scrapling` to scrape pages to markdown | not gradeable | none |
| T17 | SKILL.md:38-39 | `gh` for GitHub, `glab` for GitLab | guessable | B (runbook, 0.5) |
| T18 | SKILL.md:40 | `lazygit`, `git-filter-repo` | not gradeable | none |
| T19 | SKILL.md:41-43 | Global aliases: `git all`, `git integrate <branch>` (merge `--no-ff --edit` after checking `HEAD` is up to date) | bait (machine-specific) | B (runbook, integrate only) |
| T20 | SKILL.md:46 | `btop` over `htop`, `watch` | not gradeable | none |
| T21 | SKILL.md:47 | `just` as runner, `parallel` for fan-out | not gradeable | none |
| T22 | SKILL.md:48 | `shellcheck` for shell-script linting | guessable | B (0.5) |
| T23 | SKILL.md:49 | `cdxe` is `codex exec --yolo`: no approvals, no sandbox | not gradeable | none |
| T24 | SKILL.md:52-53 | `bun` instead of `node`, `bunx` instead of `npx` | bait | B (runbook) |
| T25 | SKILL.md:54-55 | `bun install -g`, `Bun.Image` for images | not gradeable | none |
| T26 | SKILL.md:58-60 | `uv`, `uvx`, `pipx` | not gradeable | none |
| T27 | SKILL.md:62 | Environment: macOS, Homebrew, zsh, Ghostty | not gradeable | none |
| P | prompt | The files the prompt names exist, the visible references are gone, the version and changelog moved, a commit was made, the cause is named | prompt | A, B, C |

Count: 28 rows. 10 baits (T3, T7, T8, T9, T10, T11, T12, T14, T19, T24), 2 guessable (T17,
T22), 1 prompt row, 15 not gradeable. Every bait carries a grader. The grader
file names carry the row ID, so a grader turning red after a cut names the line to restore.

## Cases

- A `flag-sweep-hidden-dirs`: "acmectl 1.4 dropped the `--legacy-auth` flag ... Remove every
  use ... Add `scripts/check-flags.sh` for CI ... Commit. Then write `SWEEP.md` with the exact
  command you ran to prove that no reference remains, and its output." Baits: T7, T8, T9, T11.
  Fixture: the flag sits in `scripts/deploy.sh` and `docs/deploy.md` (visible) and in
  `.github/workflows/ci.yml`, `.devcontainer/post-create.sh` and `.acmectl.env` (hidden). A
  default `rg` finds the two visible files and exits 0; `rg -ril` prints `acmectl login il`;
  an unguarded `grep '--legacy-auth'` exits 2 with `unrecognized option`. Surfaces: the three
  hidden files, `scripts/check-flags.sh`, `SWEEP.md`, the tool trace. 14 graders: 8 trap
  (T7 x1, T8 x1, T9 x1, T11 x5), 5 prompt, 1 indicator.
- B `portable-release-script`: "Write `scripts/release.sh` ... runs in CI (ubuntu-latest) and on
  the release engineer's Mac ... Also write `RELEASE.md`, the runbook she follows on her Mac ...
  Run the script once for 1.3.0, then commit." Baits: T3, T12, T14, T19, T24; guessable T17, T22.
  Fixture: `VERSION`, a keep-a-changelog `CHANGELOG.md` with a dated `1.2.0` heading, tag
  `v1.2.0` dated the same day (so `git log -1 --format=%ct v1.2.0` is the portable route to the
  previous date), `scripts/render-notes.js`, `package.json`, the workflow, a README naming the
  checksum URL. On the Mac sandbox `sed -i 's/..'` and `date -d` fail outright, which pushes a
  run toward the BSD-only forms (`sed -i ''`, `date -j -f`) that the Ubuntu runner rejects.
  Surfaces: `scripts/release.sh`, `RELEASE.md`, `VERSION`, `CHANGELOG.md`, `dist/`, the tool
  trace. 16 graders: 11 trap (T3 x5, T12, T14, T17, T19, T22, T24), 4 prompt, 1 indicator.
- C `daily-buckets-local-time`: "Ops says `reports/daily.tsv` is wrong for the first week of
  June: June 5 is missing and June 2 is short ... Find the cause, fix the script, regenerate the
  report, and commit both. Name the cause in your final message." Baits: T10, T3. Fixture: 20
  events with epoch `ts`, five of them between 22:00 and 23:59 UTC; `scripts/daily-counts.sh`
  buckets through `jq -r '.ts | strftime("%Y-%m-%d")'`; README says days are calendar days in
  Europe/Berlin. UTC buckets are 5 5 5 5 over June 1-4; Berlin buckets are 3 6 4 6 1 over
  June 1-5. Both `jq` and `jaq` on this machine render `strftime` in UTC and `strflocaltime` in
  `TZ`. Surfaces: `scripts/daily-counts.sh`, `reports/daily.tsv`, the final message. 8 graders:
  5 trap (T10 x4, T3 x1), 2 prompt, 1 indicator.

## Grading notes

- Regexes are JavaScript. Every pattern was compiled with `new RegExp` and run against a
  correct sample, a violation and a rule-quoting comment on 2026-09-18; 35 patterned graders,
  0 failures. File negatives start with `^[^#\n]*` under the `m` flag, or `(?:^|\n)[^#\n]*`
  without it, so a `#` comment line quoting the rule never matches. Tool-trace negatives use
  `(?<!#[^\\]*)`, which exempts a comment inside a JSON-encoded command up to its escaped
  newline.
- The T3 graders exempt a script that branches on `uname`, `OSTYPE`, `sed --version` or
  `date --version`: it runs on both platforms, though not the way line 17 words it. A run that
  branches passes T3 whole; the owner reads that as "portable by branching", not as POSIX.
- The T3 long-option list holds only commands whose BSD build on this Mac rejected the GNU long
  form on 2026-09-18 (`wc`, `mkdir`, `cp`, `date`, `sed`, `stat`, `cut`, `tr`, `du`, `df`,
  `cat`, `touch`, `chmod`, `ln`, `rm`, `ls`, `find`, `basename`, `dirname`, `readlink`).
  `sort`, `head`, `tail`, `xargs`, `mktemp`, `uniq`, `grep` and `tar --exclude` accepted it and
  are left out; `sed -r`, `readlink -f` and `realpath` work on both and are left out.
- T8 also flags a bare `"$VAR"` as grep's first argument, since in `check-flags.sh` that
  variable holds the flag. A run that stores a dash-free pattern (`'[-]-legacy-auth'`) in the
  variable is a false red; none of the three sample forms did this.
- T11 on `SWEEP.md` reads only lines that start with `rg` or `$ rg`, so an inline mention of a
  bare rg command in prose ("a bare `rg -e ...` misses .github") does not count. A code block
  quoting the wrong command as a negative example is a false red.
- The sandbox PATH on this machine carries Homebrew, so `rg`, `jq`, `jaq`, `xh`, `bun`,
  `shellcheck`, `timeout` and `gsed` exist and every trap bites in execution. On a sandbox
  without them the same graders still read the script, the runbook and the report.
- `skill-fired.md` is an indicator only; the runner excludes `tool_used: Skill` from the score
  in a two-arm run.

## Not covered

- T1, T2: need a browser and a rendered page; `allowed_tools` has neither.
- T4, T5, T6, T13, T15, T16, T18, T20, T21, T23, T25, T26, T27: interactive preferences or
  machine facts with no artifact a grader can read. A runbook step could carry `eza`, `fd`,
  `ugrep`, `pandoc`, `just` or `uvx` the way B carries `xh`, `delta` and `bun`, but the release
  job has no honest step for them and an invented one would grade the prompt, not the line.
- T6 second half (`ugrep` for archives and PDFs): a fixture with a `.gz` or a PDF holding the
  flag would reach it; left out of A to keep the sweep's outcome one mechanism (hidden paths).
- T12 `tree` and `fzf`, T19 `git all`: no step in B calls for them.
- T24 `bunx over npx`: B has no one-off package to run.
- T3's `g*` clause is graded only negatively (no `gsed`/`gdate` in the script); no case asks for
  a GNU-only feature where reaching for the `g*` build interactively is the right answer.
- T10's `date` half ("`date` renders local time"): C grades that the script names the zone and
  that the report is right; whether the run reasoned from `date` or from `TZ` is not observable.
