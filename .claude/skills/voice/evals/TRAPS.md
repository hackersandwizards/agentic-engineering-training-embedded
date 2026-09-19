# Traps in the voice skill

A trap is a line a capable model gets wrong without it. Paths are relative to the skill
directory. Case column: `A` client-reply-de, `B` linkedin-post-en, `C` price-pushback-de,
`-` not covered, `(D)` dropped after the baseline. `r` marks a regex grader, `l` an llm grader.

## SKILL.md

| ID | Line | Trap | Cases |
|---|---|---|---|
| T1 | 12 | Drafting into a thread: greeting, sign-off, one block or a stream, and the sender's own open questions come from the thread | A C (fixture only) |
| T2 | 14 | Relational vs authored register; a comment under a post is relational | B(l) |
| T3 | 15 | Relational prose always has a posture; authored prose has none | A C |
| T4 | 17 | Posture beats every layer on length, openings, closings, directness | A C |

## personal-voice.md

| ID | Line | Trap | Cases |
|---|---|---|---|
| T5 | 25 | Opener `Moin <Vorname>,`; two: `Moin ihr beiden,`; group `Moin zusammen,`; EN `Hi <Vorname>,` / `Hi everyone,` | A(r) |
| T6 | 26-27 | Sign-off `Liebe Grüße` + newline + name, no comma; EN `Kind regards,` + newline + name; a thank-you never in the sign-off | A(r) |
| T7 | 30-31 | LinkedIn message sign-off `LG` + name on one line; EN `Cheers,` + name | - |
| T8 | 32-33 | Benedikt signs `/bene`, never `Bene`, never `- Bene` | A(r) |
| T9 | 34-36 | Handover closing line verbatim: `Bei Fragen meldet ihr euch gerne jederzeit bei mir!` | - |
| T10 | 37, 94, 139-142 | `du` throughout, zero `Sie`, no client register, no formality ladder | A(r) C(r) |
| T11 | 28, 48, 50 | Three to five short sentences; median sentence 5 words; average mail 36 words | - (D: count) |
| T12 | 29 | No bullets in a mail unless listing groups or dates | C(l) |
| T13 | 40-41, 98 | The odd typo stays; zero correction messages | - |
| T14 | 43-49 | Stefan signs: `Hallo <Vorname>,` or `Hey <Vorname>,`; `Viele Grüße, Stefan` on one line | C(r, sign-off only) |
| T15 | 95-97 | Zero em-dashes, zero semicolons | A(r) B(r) C(r) |
| T16 | 106-108 | The most common mail opener is thanks, then `ich wollte kurz nachhören` | A(l) |
| T17 | 109-110 | Quick logistics reply: no sign-off; authorities and vendors: `BG` + surname | - |
| T18 | 111 | Never `Best regards`, `Sincerely`, `MfG`, `Hochachtungsvoll`, `Ciao`, a quote in the signature | - (D) |
| T19 | 116 | Hedge post-positioned: trailing `glaube ich` over leading `Ich glaube` | - |
| T20 | 117-118 | EN epistemic markers `I think`, `actually`, `basically`; never `honestly`, `in my opinion` | B(r) |
| T21 | 123-127 | Konjunktiv for asks to clients only; never soften your own commitment; no `ganz wie es dir lieber ist` tail | A(l); C regex (D) |
| T22 | 131-133 | ASCII smileys over emoji; match the thread | A(r) B(r) C(r) |
| T23 | 145-147 | Keep the personal reason the signer gave; never swap it for a professional one | A(l) |
| T24 | 148-149 | No urgency: zero `WICHTIG`, `URGENT`, `EILT`; de-escalate with `Kein Stress`, `Hat keine Eile` | - (D) |
| T25 | 101-102 | Slightly warmer than the sender, never colder; no enthusiasm against frustration | C(l) |
| T26 | 157-158 | Narrative first; bullets only for concrete deliverables, never for the pitch | A(l) C(l) |
| T27 | 160-162 | Vulnerability only with a reframe | - |
| T28 | 197-210 | Authored opening: a small observation, not a thesis; curiosity, not certainty | B(l) |
| T29 | 217-222 | No mythic framing (`The future belongs to`, `favorite weapon`) | B(l) |
| T30 | 224-232 | Closing question small and specific; no binary bait, no ladder bait, no `Have you experienced this?` | B(l) |
| T31 | 234-240 | Advice from named experience, never abstract principle | B(l) |
| T32 | 242-255 | No condescension: `without realizing`, `preaching`, `Spoiler:`; own the observation | B(r) |
| T33 | 257-261 | No passive observer language (`I've been watching`) | B(r) |
| T34 | 268-274 | Names do work in the story; no name-dropping for status | - |
| T35 | 276-295 | Technical replies drift into vendor register even when the word list passes | - |
| T36 | 297-303 | Own name last in any listing of names | - |
| T37 | 305-308 | One language per draft; every greeted name on the recipient list | - |

## prose-style.md

| ID | Line | Trap | Cases |
|---|---|---|---|
| T38 | 15-16 | Long-form main clause 15-20 words, hard ceiling 26 | B(l) |
| T39 | 10-11 | Mail sentence numbers come from personal-voice, never averaged upward: no sentence reaches 20 words | A(l) C(l) |
| T40 | 26-34 | Streckverben out: `Entscheidung treffen` -> `entscheiden`, `make a decision` -> `decide` | B(l) |
| T41 | 36-45 | Active voice by default | B(l) |
| T42 | 54-56 | Modifiers banned without a number: `deutlich, signifikant, erheblich, massiv, considerable, substantial, significant, dramatic` | - (D) |
| T43 | 60-69 | Three parties in one mail: name each company, `wir` only where the recipient is inside it | - |
| T44 | 82-93 | Abtönungspartikel (`mal`, `einfach`, `gern`, `vllt.`) stay in relational prose; the filler list is banned in authored prose | B(r) |
| T45 | 95-102 | Filler frames and EN connectors banned everywhere: `Furthermore`, `Moreover`, `In conclusion`, `It should be noted` | B(r) |
| T46 | 104-107 | No throat-clearing opener: year, definition, famous quote | B(l) |
| T47 | 129-149 | Language: stated record wins, then thread; ambiguous defaults to English | A C (prompt states it) |
| T48 | 151-154 | Umlaute, never `ae`/`oe`/`ue`/`ss` | - (D) |
| T49 | 166-169 | German prose writes `AI`, never `KI`, in every compound | - (D) |
| T50 | 171-174 | Break a rule before writing something stilted | - |

## ai-tells.md

| ID | Line | Trap | Cases |
|---|---|---|---|
| T51 | 9-20 | Contrastive reframe `not just X, it's Y`; DE `nicht nur X, sondern Y` | A(r) B(r) C(r) |
| T52 | 22-28 | Negative parallelism `no X, no Y, just Z` | B(r) |
| T53 | 30-35 | Forced triplets | B(l) |
| T54 | 37-42 | Aphorism stacking | B(l) |
| T55 | 40-43 | Announced count `Three things`, `Drei Dinge dazu:`; a count the argument needs stays | A(r) B(r) C(r) |
| T56 | 45-49 | Soft-challenge verbs `push back on`, `poke at`, `nachhaken` | B(r) C(r) |
| T57 | 67-72 | Elegant variation: repeat the noun | B(l) |
| T58 | 74-81 | Generic temporal opener `In today's`, `In a world where`, `In der heutigen Zeit` | B(r) |
| T59 | 83-93 | Four-beat paragraph: frame, expand, pivot, takeaway | B(l) |
| T60 | 95-112 | Banned openers: `Have you ever wondered`, `Let's be honest`, `Here's the thing`, `What if`, `Most people believe`, `Stop X. Start Y.`, `I used to think`, `Whether you're a` | B(r) |
| T61 | 95-101 | Bridge fillers: `at the end of the day`, `ultimately`, `in other words`, `to be clear`, `at its core`, `when it comes to`, `that said`, `it's worth noting`, `moving forward`; DE `letzten Endes`, `im Grunde`, `im Kern`, `in der Tat`, `nichtsdestotrotz` | A(r) B(r) C(r) |
| T62 | 105-111 | Copula dodges `serves as`, `stands as`, `represents`, `marks a`, `boasts`; DE `fungiert als`, `stellt ... dar` | A(r) C(r); B (D) |
| T63 | 142-168 | Sentence case; no mechanical bold; no `**Term:** description` lists | - (D) |
| T64 | 130-131 | Density bar: at most two signature words per piece, never two of one class in a paragraph | B(l: absolutes, abstraction) |
| T65 | 178-186 | Stance adverbs: `plainly, quietly, genuinely, deliberately, merely, precisely, honestly, silently, ...` | B(r) |
| T66 | 188-195 | Absolutes: `nobody, nowhere, nothing, alone, whoever, forever, ...`; name the party | B(l) |
| T67 | 151-160 | Abstraction that acts: `carries, refuses, rests, holds, settles, decides, lands, stands, governs` | B(l) |
| T68 | 206-210 | Courtroom nouns: `refusal, premise, defect, precedent, remedy, symptom, obligation, verdict, caveat` | B(r) |
| T69 | 212-218 | Coined compounds `load-bearing, chokepoint, backstop, tripwire, lever, seam, ...`; `re-verified`, `re-derived`; DE never `load-bearing` | B(r) |
| T70 | 162-169 | German classes: `schlicht, still, bewusst, nachweislich`; `niemand, nirgends, nichts`; `Anspruch, Präzedenzfall, Befund, Mangel`; abstract subject with `trägt`, `entscheidet` | A(l) C(l) |

## brand-voice.md

| ID | Line | Trap | Cases |
|---|---|---|---|
| T71 | 10 | Founders' former employers named only in proposals, bios, About copy | - |
| T72 | 15 | Humans before agents in an introduction | - |
| T73 | 69 | Vibe Coding is always the anti-pattern | - |
| T74 | 71-80 | Four KPIs verbatim: PR Throughput, AI Utilization, Change Confidence, Change Failure Rate | - |
| T75 | 84-98 | Joy is preserved: never `rediscover joy`, `enjoy programming again`, `burnout recovery` | B(r) |
| T76 | 99-102 | A number names metric, target and source; no bare `10x`, `2x faster`, `50% faster` | B(l) |
| T77 | 126-127 | Booked and forecast revenue separate; partner tier as granted | - |
| T78 | 129-135 | Clients anonymized unless a public URL shows h&w with them | B(r) |
| T79 | 137-141 | A description can identify; drop the sector first | B(l) |
| T80 | 164 | Voice exemplars verbatim only | - |
| T81 | 170-200 | Corporate buzzwords: `transform, evolve, systematic, methodology, approach, collaboration, partnership, workflow, guide (verb), tool (alone), master, proven, expert, leverage, synergies, battle-tested, force multiplier, real talk` | - (D) |
| T82 | 206-211 | Hype: `revolutionary, disruptive, best practices`; `never`/`always` as universal claims | - (D) |
| T83 | 215-221 | Corporate frames: `I just wanted to follow up`, `I hope this email finds you well`, `Please find attached`, `As per our conversation` | - (D) |
| T84 | 225-239 | No decorative Unicode: dashes, curly quotes, ellipsis, arrows, bullets, math letters, pictograph emoji | A(r) B(r) C(r) |
| T85 | 245-248 | Envelope is the authenticated account; signature is the signer's record | - |

## postures.md

| ID | Line | Trap | Cases |
|---|---|---|---|
| T86 | 7-9 | Posture from what the recipient does next, never from the work behind the message | A C |
| T87 | 26-34 | Quick reply 1-3 words; `Nicht dafür`, never `Kein Problem` as the reply to thanks; `In der Tat.` only standalone | A(r) C(r) |
| T88 | 42-44 | Written refusal: negation first (`Ne.` `Nein.`), reason second | - |
| T89 | 45-48 | Written addition of a cost or condition: confirmation first, then the number; never open on the gap | A(l) C(l) |
| T90 | 50-53 | Live objection: agreement token first; `Wobei` pivot | - |
| T91 | 55-63 | Five moves: concede by name, validate, reframe, de-scope, joint design question; person from position | - |
| T92 | 65-66 | Blunt only on external hard constraints | - |
| T93 | 68-69 | Anger is the absent smiley | - |
| T94 | 75-80 | Trainer ask: their opportunity, hook from direct exchange, 2-3 plain facts, `Hättest du Lust?` before dates, ask last, no deadline | - |
| T95 | 82-84 | Ops ask: numbered, imperative, stop condition named | - |
| T96 | 86-87 | Co-founder ask: 10-30 words, verb-first, personal reason | - |
| T97 | 89-92 | Ask form `Schickst du ...?`, not `Kannst du X schicken?`; `, ok?` tag | - |
| T98 | 94-95 | Never add `bitte` to make an ask polite | - (D) |
| T99 | 97-103 | Framing over instructing: `Alles was wir von euch brauchen`, `Wenn ihr bis zum ... Bescheid gebt` | - |
| T100 | 105-108 | Chasing: never `Erinnerung`, `any update`, `following up`, `gentle reminder`, never elapsed time | - (D) |
| T101 | 116-125 | Repair: `Ah. Shit. Sorry.`, 3-15 words, fix in 2-4 words, no `but`; never `Entschuldigung`, `Sorry für die späte Antwort` | A(r,l) |
| T102 | 127-128 | German repair clipped, English repair expands | - |
| T103 | 132-135 | Answer the question, never the investigation | - |
| T104 | 136-138 | Teaching in second person, procedural; `you don't need to` | - |
| T105 | 134 | Comprehension checked inline, never `macht das Sinn?` | A(r) C(r) |
| T106 | 144-146 | Anthropomorphic mapping for a non-technical listener | - |
| T107 | 148-149 | `I don't know` stays on in front of clients | - |
| T108 | 153-159 | Scheduling: hyphen-bulleted named slots with date and time; never `when are you free`; personal reason for a constraint; close on a three-word question; booking link never replaces slots | A(l) C(l) |
| T109 | 165-173 | Intro note: shared experience first, warmth as a question, never broker without both sides, `PS.:` in-joke | - |
| T110 | 178-184 | Status: `So,` `FYI:` `kurze info:`; good news paired with risk; numbers bare | - |
| T111 | 193-208 | LinkedIn DM: one block; `Hey <Name>,` ok; sign-off on opener, not reply; ask in the middle; a no is a `leider` clause | - |
| T112 | 212-215 | First contact closes on an interest question, no slots, no booking link | - |
| T113 | 219-227 | Cold ask opens on their work, never on `I`; close `Would that be interesting to you?` / `Hättest du Lust drauf?` | - |
| T114 | 229-232 | To a close contact the apparatus collapses to the ask | - |
| T115 | 234-239 | Honour with a named, verified piece of their work; never fabricate it | - |
| T116 | 243-249 | Never `wir haben intern festgestellt` or any process-trouble signal; ask open, skip the why | A(r) |
| T117 | 251-255 | A constraint closes by offering to settle it together: `lass uns das zusammen abstimmen`, not `lass uns telefonieren` | A(l) C(l) |

## negotiation.md

| ID | Line | Trap | Cases |
|---|---|---|---|
| T118 | 11, 27-29 | Tactical empathy first, with action evidence, not generic thanks | C(l) |
| T119 | 14, 110 | Anchor respect; justify via fit, never via cost (`ist uns gerade lieber`) | C(l) |
| T120 | 15 | Calibrated `Wie` / `Was` questions over `Würdest du` | C(l) |
| T121 | 16, 108 | Decouple bundled asks so each can be declined | C(l) |
| T122 | 17, 45, 109 | Name secondary motives yourself | - |
| T123 | 18, 97 | Recognition frame `Board of Advisors` over `öffentlich nennen` | - |
| T124 | 25 | BATNA calm, never clutching | C(l) |
| T125 | 20, 32 | Mirror their literal phrasing, sparingly in writing | - |
| T126 | 21 | Clarify before counter: the basis question carries no counter-offer | - |
| T127 | 22 | A sweetener lapses with the offer it came with | - |
| T128 | 37 | Tier choice plus upgrade door | - |
| T129 | 50-55 | Close on `Wie würdest du das aufsetzen wollen?`; after a granted concession `Passt das für dich?` instead | C(l) |
| T130 | 58 | Power-of-no door `Wenn ein Teil davon nicht passt, sag gern Bescheid.` | C(l) |
| T131 | 61-63 | Anchor-setting when going first | - |
| T132 | 66-68 | Hold price, offer scope: `Den Preis können wir nicht weiter runter. Was wir aber machen können: Scope reduzieren auf Y.`; bound a concession by scope and start date | C(l) |
| T133 | 71-73 | Concession before claim: `Du hast recht, X ist teurer ... Der Grund ist Y.` | C(l) |
| T134 | 78-82 | An unbudgeted number names its agreement before it and its size reason after it | A(l) |
| T135 | 85-89 | High anchor then alternative; `Alles inklusive`; fait accompli in present tense | - |
| T136 | 93 | Speaker fee frame; `Was brauchst du von uns, um eine Entscheidung zu treffen?` | - |
| T137 | 95 | Training pushback: hold per-participant model with cohort cap; above the cap group size changes delivery, not price; scope reductions first (shorter, single track, fewer follow-ups); a concession shows cost basis and capacity condition | C(l) |
| T138 | 97 | Advisor setup: visibility is standard, pick the tier proactively | - |
| T139 | 99 | Scope creep: `Das geht über den ursprünglichen Scope ...` | - |
| T140 | 101 | Long-term support: name the EK gap, no apology | - |
| T141 | 103 | Intro favor: three lines, `Wenn nicht, kein Stress.` | - |
| T142 | 107-117 | Anti-patterns: bundle, hide motive, argue via cost, generic flattery, ask first, `deswegen` hinge, Konjunktiv on substance (`vielleicht wäre es möglich, dass`), counter-anchor below floor, ratio before computing, retreat to floor without a rung | C(l: bundle, cost, flattery) |
| T143 | 117-120 | Wording from postures and personal-voice; a tactic landing as ultimatum, deadline or scored comparison is the wrong register | C(l); regex (D) |

## signature-phrases.md

| ID | Line | Trap | Cases |
|---|---|---|---|
| T144 | 4-8 | Mail vocabulary is plainer than the slogan catalogue; never reach for a slogan | A(l) C(l) |
| T145 | 12-19 | Five calibration anchors | - |
| T146 | 27-28 | DM median 9-11 words, thread opener 23 | - |
| T147 | 36-39 | DM openers `Moin` 55%, `Hey` 25%; `Danke fürs Annehmen` | - |
| T148 | 43-46 | `LG /bene`; English DMs measured `Best, /bene`, `Cheers` once | - |
| T149 | 54-56 | `gern` over `gerne`, `grad`, `vllt`, `ggf.`, `nen` | - |
| T150 | 57-63 | DM ask shape: greeting, warmth question, why now, `Hast du Lust`, tail, sign-off | - |
| T151 | 64-68 | DM decline: `leider`, decline first, alternative slot, smiley | - |
| T152 | 70-87 | Ten DM phrasings: `schnacken`, `Freue mich!`, `Ich melde mich`, `Sagmal`, `oder so?`, `Kein Stress`, `Machen wir so!` | - |
| T153 | 89-104 | Exemplars read live from Gmail with `-label:os/drafted` | - |
| T154 | 203-205 | `Ehrlicherweise` is rare, a marker, not a tic | - |
| T155 | 226-233 | Qualified claims carry `in the right context` in writing | - |

## brand-vocabulary.md

| ID | Line | Trap | Cases |
|---|---|---|---|
| T156 | 3-7 | Read the published frame before rewording; quote the live page | - |
| T157 | 38-40 | Written positioning vocabulary (`Non-negotiables`, `Navigator/Driver`) stays out of mail and Slack | A(l) C(l) |
| T158 | 64-66 | `Assistant` allowed; `AI developer transformation program` allowed | - |
| T159 | 70-86 | h&w on the practices layer; the competitor is the in-house team; never head-to-head with tool vendors | - |
| T160 | 77 | Firm names in canonical casing | - |
| T161 | 58-62 | Performance patterns cite metric and source | B(l) |

## content-formula.md

| ID | Line | Trap | Cases |
|---|---|---|---|
| T162 | 7-14 | Six beats: hook, story, question, insight, impact, adventure | B(l) |
| T163 | 22-28 | Hook is a small observation; research sits mid-post, never in the hook | B(l) |
| T164 | 34-36 | The story is the credential; no `in our 20 years` preamble | B(r) |
| T165 | 24-26 | Call to adventure on LinkedIn is a closing statement the reader can act on, a question only where it is a real one | B(l) |
| T166 | 28-39 | Research-backed: lived experience first, data as validation mid-post, no source name inline, one `(Source: Name, date)` after the close; never `[Source] just put a number on why` | B(r,l) |

## intro-framework.md

| ID | Line | Trap | Cases |
|---|---|---|---|
| T167 | 7-17 | N: first name plus `hackers&wizards`; role only if it adds | - |
| T168 | 19-31 | S: an instant metaphor | - |
| T169 | 33-45 | F: one number, one story, under the numbers rule | - |
| T170 | 47-59 | A: their benefit, never `I want to grow my consultancy` | - |
| T171 | 61-71 | G: a step they can picture | - |

## pitch-framework.md

| ID | Line | Trap | Cases |
|---|---|---|---|
| T172 | 5-7 | Evidence status none: beat order only; length and phrasing from postures | - |
| T173 | 9-17 | C: their outcome first, not who you are | - |
| T174 | 69-77 | N: one door, specific time and format | - |

## slack-channel.md

| ID | Line | Trap | Cases |
|---|---|---|---|
| T175 | 9-28 | MCP Slack takes standard markdown: `**bold**`, 4-space code block, `<url\|text>`, no headers | - |
| T176 | 21, 30-31 | `•` bullet only on Slack | - |
| T177 | 35-36 | Trainer channels in English | - |
| T178 | 37 | Thread reply: no greeting, no closing | - |
| T179 | 38 | 5,000-character ceiling | - |

## Baseline, 2026-09-17

Run against the unshortened skill, three runs per arm, results under `results/20260917T183107/`.
Two harness facts void most of it: the runner symlinked the skill into the plugin wrapper and
the sandbox denied every read behind the link, so the with-arm had `SKILL.md` and none of the
twelve overlays; and the runner discovered each case twice, once through that link, where the
`add_dirs` fixture was unreachable too. Only the first copy's without-arm is a clean
measurement, of a generic model. Repairs made on what that evidence can carry:

- Dropped (D) every grader both arms passed in every run: T18, T21 regex, T24, T42, T48, T49,
  T63, T81, T82, T83, T98, T100, T143, the Stefan greeting half of T14 and the regex half of
  T76. A generic model with no overlay does none of these, so they are not traps.
- The prompts said "I sign", which every run in both arms read as "leave the name off": every
  mail closed on `Viele Grüße` or `Beste Grüße` with no name. Now "sign it as me,
  Benedikt/Stefan".
- `max_turns` 20 to 40: one with-run hit the ceiling before writing.
- Each multi-condition llm rubric is split into one grader per move, so a fail names one thing.
  No threshold moved.
- The density bar (T64): the judge failed a post that carried none of the listed words, so
  stance adverbs (T65) and the rare courtroom nouns (T68) are regex now, and absolutes (T66) and
  the acting abstraction (T67) are one llm grader each that must quote what it counts.

Harness-void, left unchanged: every verbatim-form grader that failed 6 of 6 demands the form
the overlay states for that channel and signer (`Moin <Vorname>,` personal-voice.md:25;
`Liebe Grüße` newline `/bene` :26-33; `Viele Grüße, Stefan` :49; hyphen-bulleted slots and a
three-word close postures.md:154, 158; `(Source: ...)` content-formula.md:86; concede, hold,
door and calibrated close negotiation.md:50-73), and the file stating it was unreadable in that
run. The next run, with the skill directory copied, is the first measurement of them.
## Repair after the cut, 2026-09-17

Second baseline, skill directory copied, results under `results/20260917T191912/`. Thirteen
graders failed in both arms. Each was read against the current skill line and the six outputs
before it changed. Rows named here cite current line numbers; the cut moved lines, and every
other row still cites its pre-cut number.

- T11 count dropped: `three to five short sentences` is a per-mail budget, and both mail cases
  order three topics, so every output in both arms ran 13 to 23 sentences. The `mail-length`
  graders keep the measured half, T39: no sentence of 20 words or more (1.6% in the corpus). In
  the baseline the with-arm breached it 0 of 6 times, the without-arm 3 of 6.
- T70: the fourth class named no verbs, and the judge counted `bleibt`, `liegt` and `gehen` with
  a price or the slides as subject. `german-classes` now lists the verbs it counts, translated
  from 6c, and names the subjects and state verbs that do not.
- T12: `bullets-only-dates` failed a mail with no list and two mails whose only list was the two
  date windows. It now quotes the list lines it finds and passes an empty list.
- T143: `calm-tone` condition 3 read the two packages' contents, which the brief supplies, as a
  comparison scored at his expense. It now passes that content in any wording and fails only a
  ranking (`Niveau`, `billig`).
- T87: `Kein Problem` is banned as the reply to thanks (postures.md:32), and the regex banned it
  anywhere, so `16 Leute sind kein Problem` failed. Both `no-de-ai-tells` graders now match it
  only at the start of a sentence.
- T166: the research-backed pattern governs external research, and the fixture's survey was
  h&w's own. The fixture now attributes the survey to a fictional institute and the prompt says
  "a survey I read"; `experience-before-data` and `source-line` test the pattern on that.
- T76: `numbers-with-metric` demanded the metric in the same or the previous sentence, which no
  line states. The window is the paragraph now.
- T67: the judge counted verbs beyond 6c's list. `abstraction-acts` now counts a closed list of
  verbs and quotes each counted clause.
- Left failing on real hits: `no-triplets-aphorisms` (T53, T54, T59) and `verb-mechanics`
  (T40, T41, T57); every output in both arms carried one. `concede-then-hold` (T132, T133) and
  `addition-confirms-first` (T89, T134, T117) were outside this repair.

## Not covered

- Channels: LinkedIn DM (T7, T111, T146-T152), Slack (T175-T179), WhatsApp and iMessage
  emoji sets (T22 beyond the ASCII check). Three cases cover mail and one post; a fourth
  case per channel is the next step.
- Postures 1, 3, 4 (English), 5, 7, 8 (T87 beyond the `Kein Problem` regex, T94-T97, T99,
  T102, T104-T107, T109, T110) and the refusal shape (T88, T90, T92, T93). Each needs its own
  situation; none fits a client mail without crowding it.
- Cold outreach and pitch (T112-T115, T172-T174) and the self-intro (T167-T171): no case is
  a first contact.
- Negotiation branches other than price pushback: secondary motive, advisor framing,
  sweetener lapse, clarify-before-counter, speaker fee, scope creep, support rate, intro favor
  (T122, T123, T126-T128, T131, T135, T136, T138-T141).
- Anchoring on the signer's own sent mail (personal-voice:15-17, T13, T153): the cases hold
  the greeting and sign-off forms cold on purpose. A fixture with the signer's sent mail
  would hand the forms over and hide whether the skill still states them.
- T43 (three parties), T71, T72, T77, T80, T85, T156, T158-T160: proposals, bios, agent
  introductions and revenue statements are outside the three situations.
- T35 vendor register on a technical reply: needs a technical-opinion thread.
- T36 own name last: no case lists two names.
- T50 (break a rule before stilted), T19 (post-positioned hedge), T154, T155: judgement
  calls that an llm grader would score inconsistently.
- Skill conflict found while extracting, for the owner: `personal-voice.md:31` sets the
  English LinkedIn sign-off to `Cheers,` while `signature-phrases.md:45` measures
  `Best, /bene` 61 times against `Cheers` once, and `postures.md:199` repeats the once.
  `personal-voice.md:8-10` says What leads wins, so the measured form is overruled by a
  stated one. Not graded.
