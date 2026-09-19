# Traps in `delegation`

A trap is a line a capable model gets wrong without it (bait), one it would follow on its own
(guessable), or one the case's prompt itself demands (prompt), so the baseline arm passes it
without the skill. Only a bait measures the skill; a guessable or prompt row is graded where the
grader was cheap and its red would still name a line. Lines are `SKILL.md` at 48 lines. Cases:
A = `codex-runbook-tiers`, B = `hero-image-release`, C = `mail-handoff-brief`. Every case builds
its own repository in `fixture.sh` (git, coreutils, python3; no environment) and names no company,
client or record from any real repository. The run has no `Agent` tool, so each case grades the
delegation the run would issue: a plan file with every brief in full, plus the final message.

| ID | Line | Trap | Kind | Cases |
|---|---|---|---|---|
| T1 | 13 | The default is what `.codex/config.toml` sets, the repository's own before `~/.codex/config.toml` | guessable | A (through T2: the json step names the config's model) |
| T2 | 14 | Set in a repository, the default is `gpt-6-astra` at `low`, plan mode at `high` | guessable | A (json step on astra) |
| T3 | 18 | Astra low for everyday coding | bait | A (json flag and README typo at low; the typo baits a tier below) |
| T4 | 19 | Astra high for planning, hard bugs, architecture, final review | bait | A (race fix and final review at high) |
| T5 | 20 | Luna high for eval runs, where the fixture is fixed and volume sets the cost | bait | A (eval run on luna at high) |
| T6 | 22 | Astra accepts low to max and has no `none` | guessable | A (no codex step at none or minimal) |
| T7 | 23 | `codex exec --model` overrides the config per invocation | bait | A (luna on the command line; config untouched) |
| T8 | 27-30 | Codex hands Claude every piece of authored copy the voice rules cover; its own conversation with the user it writes itself | bait | A (client mail through `claude -p`) |
| T9 | 32-35 | Gather and verify the facts, then one `claude -p` call carrying sender, recipients, language, purpose, must and must-not, subject and body | guessable | A (subject, language and signature in the mail brief) |
| T10 | 38-39 | Check facts, content correctness and length; never phrasing or tone | bait | C (weekday and link found; no tone finding) |
| T11 | 39-40 | On a finding, call `claude -p` again with the previous text plus the concrete finding | bait | C (second call; previous text plus findings) |
| T12 | 40-41 | Deliver the output verbatim; any text change goes through another `claude -p` call | bait | C (verbatim in the brief; draft untouched) |
| T13 | 45-46 | Claude starts Codex only for a capability Claude lacks, image generation today, and never to author text | bait | B (image to codex; changelog, version and mail stay with self) |
| T14 | 48 | Verify what a run did with `git log`, never from its own summary | bait | B (report claims two edits git shows nothing of) |

Count: 14 rows. 10 baits, 4 guessable, 0 prompt-only. Every bait carries a grader.

## Cases

- A `codex-runbook-tiers`: "Write the runbook at plan/runbook.md ... one `## Step:` per piece with
  `Command:`, `Model:`, `Effort:`, `Brief:`." Baits: T3, T4, T5, T7, T8. Guessable: T2, T6, T9.
  Fixture: `.codex/config.toml` sets astra at low with plan mode at high; ISSUES.md holds a race
  reproducing one run in thirty, a `--json` flag and a README typo; `evals/` holds forty fixed
  cases and a runner; `brief/client-mail.md` holds the facts of a German client mail. Surfaces:
  `plan/runbook.md`, `.codex/config.toml`. 15 graders: 13 regex, 1 file_exists, 1 indicator.
- B `hero-image-release`: "Prepare release 1.4 ... write the plan first at plan/delegation.md
  ... then carry out the steps whose executor is `self`." Baits: T13, T14. Fixture: TOOLING.md
  says work is delegated through `codex exec` and that Codex carries the image tool; thirteen
  commits since `v1.3.0`; `codex-runs/2026-09-10-hero.md` claims three edits of which the commit
  shows one, so `docs/index.html` still carries the 1.2 alt text. Surfaces: `plan/delegation.md`,
  `CHANGELOG.md`, `release/announcement.md`, the tool trace, the final message. 11 graders:
  6 regex, 1 llm, 1 tool_used, 2 file_exists, 1 indicator.
- C `mail-handoff-brief`: "out/mail.txt is the draft that `claude -p` produced ... Write
  plan/deliver.md ... do not change out/mail.txt and do not write out/final.txt." Baits: T10, T11,
  T12. Fixture: the draft carries two factual errors (Wednesday for Thursday, link 4171 for 4711)
  and three correct things that bait a tone finding (the opener "quick one:", the product name
  in lowercase as the facts prescribe, one 51-word sentence). Surfaces: `plan/deliver.md`,
  `out/mail.txt`, the tool trace, the final message. 11 graders: 5 regex, 2 llm, 2 tool_used
  (one on Bash, one on Write), 1 file_exists, 1 indicator.

## Grading notes

- Regexes are JavaScript. Field names (`Model:`, `Effort:`, `Command:`, `Executor:`) are matched
  at a line start after optional list or emphasis markers, so a brief that quotes the rule in
  prose ("everyday coding: effort low") does not satisfy a positive grader whose field says
  otherwise. Step windows stop at the next `## ` heading.
- The two negatives on codex briefs in B carry a lookbehind for "not", "never", "no", "not to"
  and "never to", so "do not edit CHANGELOG.md" in the image brief does not count as a violation.
  "I add the hero line myself" inside a codex brief would; a brief phrased that way is a false
  red to read past.
- The Bash grader on `out/final.txt` in C matches a write at a command start or after `;`, `&`,
  `|` or a newline, and skips a `Command:` or `Brief:` line, so a heredoc that writes the plan
  does not count. The Write grader matches `file_path` only.
- `file_exists` counts only files created during the run, so the config's survival in A is
  graded through its contents.
- `tool_used` graders with `min: 0, max: 0` carry `arm: both` so the no-plugin arm is scored on
  them too. `skill-fired.md` is an indicator only; the runner excludes `tool_used: Skill` from
  the score in a two-arm run.
- `t14-git-log-read` fires on any `git log`, which the changelog piece demands anyway, and
  `t14-undone-named` fires on any mention of `docs/index.html`, a repeat of the report's claim
  included. Both are cheap positives; the llm grader `t14-report-not-trusted` carries the
  judgement on T14.
- Each llm grader asks one recognition question: T10 whether any finding concerns phrasing or
  tone; T11 whether the corrected text comes from `claude -p` given the previous text plus the
  findings rather than from Codex's own edit; T14 whether the final message says the run did
  not finish and names the alt text.

## Not covered

- T1's precedence half, the repository's config before `~/.codex/config.toml`: the run has no
  home directory under `env -i`, so a user config cannot be planted. A fixture that sets `HOME`
  is not available to the scaffold.
- T2's plan mode at high: no case runs codex in plan mode. A step "plan the 2.4 work" with a
  `--plan` flag would reach it, but the flag is not in the skill and would be a guess.
- T6's upper tiers, `xhigh` and `max`: no piece of work in A calls for them, and the graders
  accept only `high` where the skill says high, so a run at `xhigh` reads as a miss on T4/T5.
- T8's second half, that an agent's own replies, questions and status updates are its own to
  write: every case's final message is the run's own conversation, and grading that it was not
  routed through `claude -p` would score a habit the baseline has anyway.
- T9 beyond three facts: purpose, must and must-not are demanded by the fixture's brief file,
  so a grader on them scores the prompt, not the skill.
- T14's second half in A: the runbook is written before any run, so there is no run summary to
  distrust there.
- The effort override per invocation: the skill names `--model` only (line 23), so T5 at high
  on luna needs an effort flag the skill does not state; the graders accept any `Effort: high`
  and do not check how the command line sets it.
