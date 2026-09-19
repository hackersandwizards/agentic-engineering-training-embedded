# Traps in the agent-feedback skill

A trap is a line a capable model gets wrong without it (bait) or gets right unprompted
(guessable). Lines refer to `SKILL.md` (S) and `correction.md` (C) in this skill directory. Cases:
A = `memory-licensed-skip`, B = `mirror-drift-release-gate`, C = `trim-cli-skill`. A case never
names the skill; the with-arm indicator is the `skill-fired` grader in each case. Every case
builds its own setting in `fixture.sh` and depends on no other repository.

A fixture keeps skills, rules and agent files out of `.claude/`. The run is headless in `default`
permission mode, and `.claude/skills`, `.claude/rules`, `.claude/agents` and `.claude/commands`
are protected paths there: `Edit`, `Write` and a Bash command naming such a path are refused, no
allow rule lifts that, and the graders then read the seed file in both arms. Cases A and C hold
them under `agent-config/`, case B under `hub/`. `.claude/agent-memory/` is not protected and
keeps the memory file. A sync script's own `cp` into `repos/*/.claude/` is not seen by the
command check and goes through. Every prompt says that nobody answers questions.

| ID | Line | Trap | Kind | Cases |
|---|---|---|---|---|
| S1 | SKILL.md:26-27 | Feedback and review never authorize an external action | guessable | none |
| S2 | SKILL.md:31 | Positive imperatives with explicit objects | guessable | none |
| S3 | SKILL.md:32 | A negative that carries the rule stays negative | guessable | none |
| S4 | SKILL.md:33 | Vague adverbs ("as appropriate", "when relevant") become the actual condition | bait | B C (weight 0.5) |
| S5 | SKILL.md:34-35 | Cut the history: version changes, incidents, prior bugs, verification counts | bait | A B C |
| S6 | SKILL.md:36-37 | An artifact states a rule or a measurement, never a status | bait | A C |
| S7 | SKILL.md:38-39 | A terminal phrase names the half it governs | bait | none |
| S8 | SKILL.md:40 | English instruction; quoted examples keep their language | guessable | none |
| S9 | SKILL.md:44-46 | Thin `SKILL.md` routing outward; length never forces a split | guessable | none |
| S10 | SKILL.md:47-49 | A rule's binding outranks a tidier axis; the mode the first gate locks out is the cut | bait | none |
| S11 | SKILL.md:50-52 | The invariant goes in the job file where it fires, never in the router | bait | B |
| S12 | SKILL.md:53-54 | Finish a split with a no-context walker over the whole directory | bait | none (no Agent tool in the cases) |
| S13 | SKILL.md:55-57 | A rule firing on a minority of turns gets `paths:` frontmatter or becomes a skill | bait | none |
| S14 | SKILL.md:58-61 | A cut ends with `description` and `agents/openai.yaml` `short_description` re-read against the body | bait | C |
| S15 | SKILL.md:62-64 | A parameter, validator or script over more prose when the requirement is deterministic | bait | none |
| S16 | SKILL.md:68-71 | Grep first; an existing fact makes the change a move whose second half is a deletion; one owner per behavior | bait | A (with C5) |
| S17 | SKILL.md:73-75 | A line obliging a report of a value names the field the consumer joins on | bait | none |
| S18 | SKILL.md:77-80 | A gate answers "possible" and "wanted" separately; every suppression ships with its trace | bait | none |
| S19 | SKILL.md:82-88 | Cutting a reference is a deletion, not a description; an always-on rule's citation goes, a `paths:` rule's clause is inlined; a name as data stays | bait | C |
| S20 | SKILL.md:92-96 | Widen a mandate by narrowing the opening rule until true, never by appending an exception; second mandate as its own sentence, bounded by area | bait | A |
| S21 | SKILL.md:98-100 | Narrow only where the work is that colleague's; refuse the row otherwise | bait | none |
| S22 | SKILL.md:102-104 | Name the artifact a run produces in one noun before citing a rule against it | bait | none |
| S23 | SKILL.md:106-112 | Exclusions and obligations as acts, not classes or channels; repair by splitting acts, never "except" | bait | A (with S20) |
| S24 | SKILL.md:114-116 | A tool's `--help`, schema or server instructions are a second owner; keep only what they leave out | bait | C |
| S25 | SKILL.md:120-125 | Check the sync script's `GLOBAL_RULES`, `GLOBAL_SKILLS`, `FORKS` per file; edit the hub copy, a mirror edit dies on the next sync | bait | B |
| S26 | SKILL.md:127-133 | Diff every mirror against the hub before syncing; drift the hub lacks is copied to the hub first; a declared fork is left and never lifted | bait | B |
| S27 | SKILL.md:135-136 | Commit the hub copy in the hub with paths named, then run the sync, which commits the mirrors | bait | B |
| C1 | correction.md:9-15 | Complete the requested correction first; change an artifact only when the counterfactual holds | bait | A |
| C2 | correction.md:19-20 | Improve retrieval or question timing when the missed fact was discoverable | guessable | none |
| C3 | correction.md:21-22 | Unchanged for unavailable case facts, a changed goal, or a one-off preference | bait | A |
| C4 | correction.md:23-24 | An external edit needs an observed before-and-after; never inferred from the action | bait | A (weight 0.5) |
| C5 | correction.md:25-26 | The right instruction already there: consolidate, remove conflicts, add a check; never a duplicate reminder | bait | A |
| C6 | correction.md:27-29 | Output blamed on a rule is measured against its threshold; passing output means the rule is missing | bait | none |
| C7 | correction.md:33-41 | Exactly one owner: skill or rule, `CLAUDE.md`, agent definition, agent memory | bait | A |
| C8 | correction.md:37-39 | Where the project names who owns an agent file, the edit is theirs: report the gap | bait | none |
| C9 | correction.md:43-45 | Content of one write belongs to the skill; whether the agent may act at all belongs to the agent definition | bait | A |
| C10 | correction.md:49-50 | A hazard the top-level session reaches is owned by an always-on rule, not an agent file | bait | none |
| C11 | correction.md:51-53 | A skipped check: repair the memory line that licensed it; a narrower restatement is widened where it stands | bait | A |
| C12 | correction.md:54-55 | One agent failing earns a bound in its own file; a second failing promotes it into the rule | bait | none |
| C13 | correction.md:59-61 | Never edit a generated mirror, plugin cache or customer-specific artifact as source of truth | bait | B (with S25) |
| C14 | correction.md:62-63 | Search for overlap and contradiction; remove no-ops and duplication while there | guessable | C (partial, via S5 and S6) |
| C15 | correction.md:65-66 | Add only the reusable invariant; never the customer, work product, wording, answer or outcome | bait | A B |
| C16 | correction.md:67-68 | Validate with the repository's checks; forward-test only where nothing live mutates | guessable | A (weight 0.5) |
| C17 | correction.md:70 | Report one line naming the artifact and the generalized change | guessable | none |

Count: 44 traps, 35 bait, 9 guessable. Bait with a grader: 22 (S4, S5, S6, S11, S14, S16, S19,
S20, S23, S24, S25, S26, S27, C1, C3, C4, C5, C7, C9, C11, C13, C15). Bait without one: 13
(S7, S10, S12, S13, S15, S17, S18, S21, S22, C6, C8, C10, C12), listed under Not covered.

## Cases

- A `memory-licensed-skip`: a releaser agent skipped `check.sh` because its memory said so, the
  user rewrote its changelog line in git, asked for a one-off ordering, and widened its hotfix
  mandate. Graders: C1, C11, C5+S16, C7+C9, C15 (skill, memory), C3 (skill, memory), S6 (memory),
  S5+S6 (rule), S20 (sentence gone), S20+S23 (no exception), C4, C16.
- B `mirror-drift-release-gate`: the deploy skill is mirrored from `./hub` into three checkouts;
  beta drifted, gamma is a declared fork; the sync script adopts uncommitted hub changes and
  writes `.sync-ran`. Graders: S25+C13 (hub), S11 (router), S25+S27 (alpha via sync), S26 (drift
  lifted), S26 (fork not lifted), S26 (fork kept), S27 (`adopted=no`), S27 (paths named on
  `git add` or `git commit`; SKILL.md:135 reads either way), C15+S5, S4.
- C `trim-cli-skill`: a skill restates `bin/pkgctl --help`, carries history and a status, cites
  an always-on rule and a `paths:` rule by name, and has a Codex manifest; the user drops the yank
  mode. Graders: S24 (restated lines gone), S24 (help read), S14 (description), S14 (openai.yaml),
  S19 (always-on citation deleted, not paraphrased), S19 (scoped clause inlined), S19 (scoped rule
  not cited), S5, S6, S4, frontmatter sanity.

## Not covered

- S7: a terminal-phrase bait needs a transcript where a run parked a finding in an escape hatch;
  the grader would be an `llm` one. A fourth case around a "stop here" line could carry it.
- S10, S12: splitting a skill needs the Agent tool for the walker and an `llm` grader for the
  axis; out of scope for a three-case regex suite.
- S13: no case asks for a new rule, so no `paths:` decision arises. Add to a correction case
  whose fix is a new rule on a minority surface (for example SQL migrations) and grade `^paths:`.
- S15: no deterministic requirement with a validator at hand. A fixture with `scripts/check.sh`
  and a naming rule would carry it: grade that the check gains the assertion and the prose does
  not.
- S17, S18: join keys and gate traces are company-OS shapes; a synthetic case would restate the
  company rows. Left out on the hard constraint.
- S21, S22: judgment calls with no deterministic surface.
- C6: needs a rule with a numeric threshold, output that meets it, and a user blaming the rule.
  Fits a fourth case with a subject-line-length rule; grade that the threshold line is not
  duplicated and the missing rule is added.
- C8: needs a `CLAUDE.md` naming an owner for `.claude/agents/`; case A leaves the owner unnamed
  because S20 needs the agent file to be editable. A fourth case can invert that and grade the
  agent file unchanged plus an `llm` grader on the report.
- C10, C12: owner tests between an agent file and an always-on rule; a case needs a top-level
  session in the transcript or a second failing agent.
- S1, S2, S3, S8, S9, C2, C14, C17: guessable, no grader.
