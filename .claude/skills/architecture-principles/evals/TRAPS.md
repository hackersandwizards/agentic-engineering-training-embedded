# Traps in `architecture-principles`

A trap is a line a capable model gets wrong without it (bait) or one it would follow on its own
(guessable). Only a bait earns a grader; a guessable line gets one only where it is cheap. A
prompt row is a demand of the case's own prompt, graded so a run that ignores the prompt is
visible. Line numbers are `SKILL.md` at 91 lines. Cases: A = `notifications-build-or-buy`,
B = `feed-importer-refactor`, C = `platform-proposal-review`. Every case builds its own
repository in `fixture.sh` (git, coreutils, python3; no environment) and names no company,
client or record outside itself. Grader names carry the row ID.

| ID | file:line | Trap | Kind | Case |
|---|---|---|---|---|
| T1 | SKILL.md:21,40 | Architecture splits work between teams; one team gains nothing from a second deployable, and every new service is debt until proven | bait | A `t1-no-separate-deployable` |
| T2 | SKILL.md:45-46 | Sensible defaults and low-tech coupling: no gRPC, mesh, broker, second language or second datastore for a problem HTTP and Postgres carry | bait | A `t2-boring-coupling` |
| T3 | SKILL.md:70-71 | Build or buy runs the five cost levels: license, integration, operation, opportunity, migration | bait | A `t3-cost-five-levels` |
| T4 | SKILL.md:69-70 | Build or buy is evaluated on functional, technical and operational complexity plus unique business value | bait | A `t4-complexity-axes` |
| T5 | SKILL.md:29 | A running system with minimal functions outranks discussing concepts, so the first shipment is one notification reaching a customer | bait | A `t5-first-ship-running-slice` |
| T6 | SKILL.md:38-39 | Contexts communicate through domain events, not an inline call in the order flow or a polled shared table | bait | A `t6-domain-event` |
| T7 | SKILL.md:33 | Everything in production is owned: the ADR names who runs the path and handles provider failures | guessable | A `t7-owner-named` (0.5) |
| T8 | SKILL.md:69-71,83 | Delivery has no unique business value, so sending is bought and the shop keeps deciding what fires when | guessable | A `t8-delivery-bought` |
| T9 | SKILL.md:47 | Decisions in public with the why: the ADR rejects each alternative with a reason | prompt | A `t9-adr-alternatives` (0.5) |
| T10 | SKILL.md:52 | Temporal decomposition: modules named for execution steps each carry the same format knowledge; restructure by knowledge | bait | B `t10-temporal-decomposition-gone` |
| T11 | SKILL.md:52 | Pass-through methods: a class whose methods only forward to collaborators goes | bait | B `t11-pass-through-removed` |
| T12 | SKILL.md:52 | Shallow module: three one-line wrappers over str methods are inlined and the module deleted | bait | B `t12-shallow-module-gone` |
| T13 | SKILL.md:53-54 | Implementation contaminates interface: the caller stops creating the cursor the writer needs | bait | B `t13-cursor-out-of-interface` |
| T14 | SKILL.md:54 | Vague names: `tmp` and `info` renamed for what they hold | guessable | B `t14-vague-names-gone` |
| T15 | SKILL.md:53 | A comment repeating the code goes | guessable | B `t15-comment-repeating-code-gone` (0.5) |
| T16 | SKILL.md:52 | Information leakage: the column layout parsed once, the rest on a parsed record | bait | B `t16-format-known-once` |
| T17 | SKILL.md:53 | Special-general mixture: the promo branch leaves the general writer | bait | B `t17-special-case-separated` |
| T18 | SKILL.md:21,40 | Services sized to team capacity, not nano-services: 14 services for two teams of four is rejected and the count tied to the teams | bait | C `t18-services-sized-to-teams` |
| T19 | SKILL.md:46 | Low-tech coupling: gRPC plus service mesh replaced by HTTP, JSON or event streaming, not endorsed | bait | C `t19-boring-coupling` |
| T20 | SKILL.md:30 | MTTR over MTBF: the reliability answer is recovery time, not a longer regression window | bait | C `t20-mttr-over-mtbf` |
| T21 | SKILL.md:44 | Trunk-based development and deploy on every green build answer gitflow | bait | C `t21-trunk-based` |
| T22 | SKILL.md:34 | Delegate implementation, never understanding: agent-maintained payments nobody reads is refused | bait | C `t22-retained-expertise` |
| T23 | SKILL.md:38,59 | Shared database across team boundaries is an anti-pattern; data owned per context | guessable | C `t23-shared-database` |
| T24 | SKILL.md:38,59,87 | A monolithic frontend both teams commit to is an anti-pattern; UI owned per context | bait | C `t24-frontend-per-team` |
| T25 | SKILL.md:38-39,59 | No domain events and a four-hop synchronous chain are anti-patterns; events and eventual consistency | bait | C `t25-domain-events` |
| T26 | SKILL.md:33 | You build it, you run it: a platform team running what product teams built is rejected | bait | C `t26-build-it-run-it` |
| T27 | SKILL.md:62 | Heroism culture is waste: praised night-time fixes are named as a problem | bait | C `t27-heroism-named` |
| T28 | SKILL.md:63 | Approval bottlenecks and process gates: three approvals and the change board named as a cause | guessable | C `t28-approval-bottleneck` (0.5) |
| T29 | SKILL.md:63-64 | Oversized work packages and unfinished tickets: the 21- and 34-point work open since June is read and named | guessable | C `t29-oversized-unfinished-work` |
| T30 | SKILL.md:30 | Conway's Law names why the service count and the frontend follow the two teams | bait | C `t30-conway` (0.5) |
| T31 | SKILL.md:31,45 | Minimal variation: a free stack per service is rejected | bait | C `t31-minimise-variation` |
| T32 | SKILL.md:58 | Missing test environments: decommissioning staging is rejected | guessable | C `t32-test-environment` (0.5) |
| T33 | SKILL.md:48 | TLS everywhere: plain HTTP between services is rejected | guessable | C `t33-tls-everywhere` (0.5) |
| T34 | SKILL.md:22 | Principles over rules: teach judgment | not gradeable | none |
| T35 | SKILL.md:23 | Changeability outranks correctness | bait | none |
| T36 | SKILL.md:24-25 | The Three Ways and the Five Ideals as vocabulary | guessable | none |
| T37 | SKILL.md:30 | Short build-measure-learn cycles; uncertain requirements clear up by building | guessable | none |
| T38 | SKILL.md:32 | Non-functional coverage, react with urgency | guessable | none |
| T39 | SKILL.md:41 | Evolutionary architecture, sacrificial architecture, throw away and rewrite | bait | none |
| T40 | SKILL.md:42-43 | Cloud native, 12-factor, stateless, scale by instances | guessable | none |
| T41 | SKILL.md:52-54 | Overexposure, repetition, conjoined methods, hard-to-pick names, hard to describe, nonobvious code | bait | none |
| T42 | SKILL.md:58 | Tight coupling between systems, manual deployments | guessable | none (C names the runbook by prompt) |
| T43 | SKILL.md:61-64 | Missing focus, context switching, long wait times, knowledge silos, meeting overload, scope creep, excessive handoffs, bugs as unplanned work, manual toil | bait | none (C's fixture plants each) |
| T44 | SKILL.md:66-67 | Systemic issues: craftsmanship, domain understanding, systems thinking, experimentation, learning, security afterthought | bait | none |
| T45 | SKILL.md:75-91 | Techniques, Principles, Practices: the three-column vocabulary for training content and proposals | prompt | none |

Count: 45 rows. 28 baits, 14 guessable, 2 prompt, 1 not gradeable. 33 rows carry a grader (T1
to T33), 23 of them baits; 12 rows carry none (T34 to T45), 5 of them baits: T35, T39, T41,
T43, T44.

## Cases

- A `notifications-build-or-buy`: "Decide it: build or buy, and how it fits into this codebase
  and this team. Write the decision as docs/adr/0004-customer-notifications.md ... say what
  ships first." Baits: T1, T2, T3, T4, T5, T6. Surfaces: the ADR file, the final message. The
  fixture's order flow calls collaborators inline and no event bus exists, so an inline
  `notifications.send()` is the path of least resistance; the request's proposal A is a Go
  service with gRPC, NATS, Redis and a polled table.
- B `feed-importer-refactor`: "Restructure it so that the next format change is small ... Don't
  commit ... end your message with the output of `git status --short`." Baits: T10, T11, T12,
  T13, T16, T17. Surfaces: `importer/cli.py` (the tests import it, so it survives), the git
  status in the final message (deletions and renames), the final message.
- C `platform-proposal-review`: "Review docs/proposal-platform-2027.md ... what is right, what is
  wrong, and what you would do instead ... Say why we are slow. Write both as
  docs/review-platform-2027.md." Baits: T18, T19, T20, T21, T22, T24, T25, T26, T27, T30, T31.
  Surfaces: the review file. The proposal endorses each anti-pattern with a plausible reason
  (MTBF target, latency, freed engineers, cost), so a review that judges on the proposal's own
  terms passes the baits' violations.

## Grading notes

- Whether a `regex` grader passes or fails on a file the run deleted is unstated in the
  plugin-evals docs, so no grader targets a file a refactor may remove: B's deletions are read
  off the `git status --short` the prompt asks for (`D  path`, ` D path`, `R  old -> new`, all
  matched by `(?:^|\n)\s*[DR]\S*\s+path`), and B's code negatives target `importer/cli.py`
  only.
- Negatives on code use a code shape (`ImportService\(`, `cursor\s*=|\.cursor\(`,
  `\b(?:tmp|info)\s*=`) so a comment quoting the rule does not match.
- Positives on prose (C) use `flags: i` and several phrasings; each was tested against a
  correct sample, a violation and a paraphrase that must not count. The `llm` graders carry one
  recognition criterion each and read the Decision section, not the alternatives, so a
  rejected option is not scored as a chosen one.
- `file_exists` counts only run-created files; both ADR and review are new paths.
- `skill-fired.md` is an indicator only; the runner excludes `tool_used: Skill` from the score
  in a two-arm run.
- Fixtures verified on 2026-09-18 under `env -i PATH=/usr/bin:/bin:/usr/local/bin:/opt/homebrew/bin bash fixture.sh`
  in an empty directory: A and B run `python3 -m unittest` green, B's CLI imports the sample
  feed, C's CSV has 18 rows with three features and two unplanned fixes done.

## Not covered

- T35, changeability over correctness: a task where the changeable design and the correct one
  differ needs a planted bug the model is told to leave, which no honest prompt asks for.
- T39, sacrificial architecture: whether B rewrites or patches has no surface distinct from the
  refactor graders, and "throw away" on a repository this size is indistinguishable from a
  rename.
- T41, the remaining Ousterhout flags: overexposure needs a configuration surface, conjoined
  methods a pair whose contracts lean on each other, and nonobvious code a reader; each needs a
  second refactor fixture.
- T43, the rest of the process-waste list: C's fixture plants eleven meetings, the dev-QA-release-ops
  chain, the unplanned tickets and the cache command only Ben knows, but a grader per item would
  score diagnosis prose a capable model produces from the numbers alone; T27 and T28 stand in.
- T42, manual deployments and tight coupling: C's prompt points at the runbook, so naming it is
  a prompt effect, not a skill effect.
- T36, T37, T38, T40, T44, T45: vocabulary and values with no observable in these three tasks.
  A cut of any of them is unproven by this suite either way.
- T34: a meta-claim about the skill's own form.
- The `description` triggers (SKILL.md:4-12): the with-arm indicator shows whether the skill
  fired on a design, a refactor and a review prompt, and nothing here tests the skip clause
  for routine implementation.
