# Brand Voice: hackers&wizards

Sets what h&w sounds like, which words it refuses, and how it talks about results. Owns the brand voice, the canonical banned words, and the Schwartz awareness-stage messaging.

Apply when writing **anything that represents h&w externally**: proposals, posts, slides, website copy, emails, Slack to clients, speaker outreach, talks. Skip for internal commit messages, code comments, raw notes.

## Brand positioning principles

How h&w shows up in any sentence about itself or its work:

- **Authenticity first.** "We write code, we scale teams, we know the pain firsthand." Lead with lived experience, not theory.
- **First-person plural authority.** Use "we" to ground claims. Name the [client]/[client]/[client]/[client] background in: client-facing proposals, About copy on the website, conference bios, podcast intros. Skip in: internal Slack, code reviews, casual replies.
- **Empowerment over dependency.** "We enable teams to succeed without us." Capability transfer is the goal, not retainer lock-in.
- **Excellence enables speed.** Quality is the productivity story, not a tax on it. Frame quality and velocity as the same thing.
- **Humble expertise.** "Every situation teaches us something new." Confident, learning-oriented. Self-deprecation is allowed and welcomed (see `personal-voice.md`).
- **Responsibility-focused.** Long-term team health and sustainable outcomes. Avoid quick-win framing.

## Writing substance: what h&w talks about

When in doubt whether a claim is on-brand, run it against this list:

- **Experience-based claims:** back assertions with firsthand knowledge and real client examples.
- **Sustainability language:** "long-term", "sustainable", "over time", "preserving" outcomes.
- **Capability building:** "internal capability", "knowledge transfer", "independent improvement".
- **Learning orientation:** acknowledge every context offers fresh insights.

The five recurring themes (use to ground longer-form content):

1. **Agentic Engineering Practices:** elevating teams from scattered AI adoption to confident AI practitioners. Vibe Coding is fine for prototypes, not for lasting software.
2. **Context Engineering Foundations:** building multi-layer context architectures that make agents effective. Context engineering as the bottleneck.
3. **Quality at Scale with Agents:** AI-friendly architecture, testing strategies, quality gates for agentic development.
4. **Team Practices and Change Management:** how team dynamics shift when agents join, and how to make it stick. AI adoption is like Agile twenty years ago, culture, not tools.
5. **Programming Joy Preservation:** purpose, fulfillment, and craft in agentic software development.

Anchor posts, talks, and proposals to one of these. Consistency across channels and over time is the win.

## Audience

CTOs, VPs of Engineering, Tech Leads, and senior developers. Peer language, not vendor language. They've seen every consulting deck. Surprise them with specifics they haven't.

## Core positioning: the verbatim set

The terms h&w uses consistently. Use verbatim when the concept fits. The consistency builds the category.

### Primary headlines (priority order)

1. **"Elevate Your Teams"**: main value proposition.
2. **"Faster Delivery. Better Code. Fulfilled Teams."**: supporting tagline.
3. **"From scattered AI adoption to confident AI practitioners"**: journey positioning.

### Core positioning terms (use verbatim)

- **"Agentic Engineering"**: primary term. The h&w framework that unifies autonomous software development: AI-assisted development, prompt engineering, context engineering, modern software engineering, pragmatic programming.
- **"Agentic Product Engineering"**: extension of Agentic Engineering into the product domain (user testing, personas, AI-assisted prototyping, spec-driven development).
- **"Functional Agentic Engineering"**: functional programming as the technical paradigm: immutability, pure functions, composability applied to AI-assisted development.
- **"AI-Assisted Development"**: key aspect of Agentic Engineering.
- **"AI-Augmented Development"**: alternative term.
- **"Agentic engineering practices"**: the implementation.
- **"Structured AI development"**: process-focused approach.

### Components unified under Agentic Engineering

These are framed as **components of** Agentic Engineering, not competitors to it:

- **"Context Engineering"**: managing AI conversation context and memory. Core component.
- **"Modern Software Engineering"**: contemporary practices integrated with AI.
- **"Prompt Engineering"**: structured AI interaction techniques.
- **"Pragmatic Programming"**: practical, results-oriented development.
- **"Extreme Programming"**: agile practices adapted for AI-assisted development.
- **"Vibe Coding"**: the **anti-pattern** Agentic Engineering replaces. Always frame as the problem, never the solution.

## Competitive positioning

h&w sits on the **methodology and enablement layer**, not in competition with AI-coding tools. The real competitor is the client's in-house transformation team trying to build the setup themselves. The full stack frame and application rules live in `brand-vocabulary.md`.

## The four core client-engagement KPIs

Standard KPIs measured in every h&w client engagement. Reference them when discussing measurability. They replace any vague *"we improve productivity"* claim.

1. **PR Throughput:** merged PRs per week/team. Measured via Git Analytics (history retroactively available).
2. **AI Utilization:** % of PRs/tasks with AI support. Measured automatically via Claude Code co-author tags, or via PR-template checkbox.
3. **Change Confidence:** developer self-reported confidence in changes, 1-5 scale. Monthly survey, baseline at engagement start.
4. **Change Failure Rate:** % failed builds/deployments on test stage. Measured via CI/CD (hardest to measure, team-dependent).

Default phrasing when no specific metric applies: *"measurable through PR throughput, AI utilization, change confidence, and failure rates."*

## Developer well-being language

Position AI as **preserving** programming joy, not recovering it.

Good: Use:
- *"programming joy"*, *"programming spark"*
- *"developer confidence and fulfillment"*
- *"sustainable engineering practices"*
- *"cognitive load reduction"*
- *"long-term career health"*
- *"preserve the craft"*

Bad: Avoid (failure mode in parens):
- *"burnout recovery"* (implies the developer is already burned out)
- *"therapy"* / psychological terms (medicalizes a craft conversation)
- *"enjoy programming again"* (implies the joy is lost)
- *"rediscover joy"* (same, implies lost)

## Messaging by awareness stage (Schwartz framework)

Eugene Schwartz's five awareness stages calibrate **what to say** based on where the reader sits. Apply when writing the website, content marketing, posts, or any cold-channel copy where the reader's awareness is unknown. Less relevant for direct emails to known contacts.

| Stage | Reader state | Opening move | Failure mode |
|-------|--------------|-------------|--------------|
| **1, Unaware** | CTO senses developer-productivity friction but hasn't named it | Open with the friction, not the solution. *"Declining team velocity. Code-quality drift. Tech debt nobody's tracking."* No mention of AI yet. | Leading with "AI" loses readers who haven't connected their pain to AI adoption. |
| **2, Problem-Aware** | Knows there's an AI-adoption issue, hasn't connected it to systematic practices | Amplify the specific pain (longer review cycles, junior outputs, morale drift) before naming the cause. | Skipping to solutions reads as a sales pitch and loses the reader who hasn't felt the pain explicitly. |
| **3, Solution-Aware** | Researching different approaches to AI adoption | Position the **category**: context engineering vs prompt engineering vs vibe coding. Educate on the differences. | Pitching h&w specifically before the reader has chosen a category framing makes us sound interchangeable with tooling vendors. |
| **4, Product-Aware** | Comparing consultancies and training providers | Differentiate with proof: client names, metrics, testimonials, FAQ that addresses the specific objections of an evaluator. | Generic value-prop copy here loses to competitors who name specific results. |
| **5, Most Aware** | Decided, needs final motivation | Scarcity ("3 Q4 spots remaining"), clear next step, time-bounded offer. | Re-explaining the value at this stage delays the action. |

**Funnel order:** unaware -> problem-aware -> solution-aware -> product-aware -> most-aware. Website pages should serve all five stages so readers can enter wherever they are and progress.

**On the website specifically:** the homepage opens at stage 1. The methodology page lives at stages 2-3. The Work Together page is stages 4-5.

## Performance language: the rule

Generic multipliers without a measurement source are corporate filler. Readers stop trusting the writer. When citing performance, name **the metric, the target, and the source**. All three.

**Banned without a named source:**
- Bad: "10x improvements / speed / efficiency / productivity"
- Bad: "2x faster", "5x", any bare multiplier
- Bad: "Order of magnitude improvements"
- Bad: "50% faster" without naming what was measured
- Bad: "I've helped many companies"
- Bad: Any percentage claim without metric + target + origin

## Voice exemplars: verbatim only

All "voice anchor" or "real exemplar" lines in any voice rule MUST be exact quotes from confirmed real sources: sent emails, Slack messages, Fathom transcripts, the user's own published posts. Never fabricate them; a fake exemplar poisons every draft that calibrates against it.

If real lines aren't available for a section, leave a gap-note saying real verbatim lines need to be sourced. Don't fill with invention.

## Banned words

The canonical list. Each entry includes the failure mode so the rule stays enforceable when an edge case shows up.

### Corporate buzzwords

| Word | Why banned | Use instead |
|------|-----------|-------------|
| **Transform / Transformation** | Overused buzzword. Exception: "Transform scattered AI adoption into systematic practices" is approved for website hero copy only. | "convert", "shift", "rebuild", or name the actual change |
| **Evolve / Evolution** | Same overuse, vague trajectory framing | name the specific change |
| **Systematic** | Consultancy jargon. Exception: "Systematic thinking" and "Systematic practices" stay allowed in website/marketing copy. | "structured", "organized" |
| **Methodology / Method / Methodical** | Academic-consultancy term, distances from action | "framework", "practices", "way of working" |
| **Approach** | Vague consultancy hedge | name the specific thing being done |
| **Collaboration** | Vague, overused | name what specifically is shared |
| **Partnership** | Corporate speak | "working together", "joint engagement" |
| **Communication** | Generic | name the specific channel or message |
| **Workflow** | Process jargon | name the specific sequence |
| **Guide** (as verb) | Patronizing | "show", "walk through" |
| **Discipline** | Rigid/military connotation | "practice", "habit" |
| **Chaos** | Overly dramatic | name the actual disorder |
| **Tool** (alone) | Too generic | name the actual product |
| **AI** (when used generically) | Too broad | "Claude Code", "agentic engineering", or the specific product |
| **AI coding tools / assistants** | "Coding" too narrow | "agentic engineering tools" |
| **AI augmentation** | Too technical/niche | "AI-assisted development" |
| **Master / Mastery** | Overused achievement framing | "proficiency", "competence", "excellence" |
| **Proven / Proved** | Overused credibility claim | "tested", "validated", "established" |
| **Insatiable** | Hyperbolic | "relentless" |
| **Expert / Expertise** | Overused credibility claim | "mentor", "practitioner", "knowledge" |
| **Individual** (as redundant qualifier) | Adds nothing | drop it, just "productivity", "developer experience" |
| **Maintain / Maintaining** (in business contexts) | Stale corporate verb. Exception: technical contexts ("maintaining code", "maintaining systems") stay allowed. | "preserve", "sustain", "ensure", "keep" |
| **Turn** (as overused action) | Overused | "convert", "empower" |
| **Synergies** | Buzzword | name the specific overlap |
| **Leverage** | Buzzword | "use", "build on", "apply" |
| **Battle-tested** | Reads like marketing copy. Never appears in the user's real writing. | name the actual production track record |
| **Force multiplier / Disproportionate** (gains, returns) | Strategic-deck vocabulary | name the actual leverage or the actual ratio |
| **Real talk:** | Authenticity theatre, not authenticity | drop the frame, lead with the claim |
| **Pre-training state / post-training state** | Too abstracted | concrete time anchor: "first hour", "week six" |

### Hype vocabulary

These signal marketing breathlessness rather than real claims:

| Word | Why banned | Use instead |
|------|-----------|-------------|
| **Revolutionary** | Overused hype | name the actual change |
| **Disruptive / Disruption** | Overused hype | describe what's being replaced |
| **Best practices** | Frames opinions as universal truth, kills nuance | *"what works in this context"*, *"in my experience"*, name the constraint |
| **Never** / **Always** (as universal claims) | Respect context, almost no rule is absolute | name the condition: *"on a tight deadline,"* *"with a junior team"* (carve-out: literal accuracy is fine, *"never use eval()"*) |

### Corporate sentence frames

Empty filler that survives its own deletion:

- "I just wanted to follow up" -> "Moin, wie sieht's aus mit [topic]?"
- "I am writing to inquire" -> state the question
- "I hope this email finds you well" -> "Moin {Name}"
- "Please find attached" -> "Hier wie besprochen: [link]"
- "As per our conversation" -> name the conversation: "Wie gestern besprochen"

### Banned style: no decorative Unicode

Screen readers can't read decorative Unicode. Customer-facing text (LinkedIn posts, emails, website copy, proposals) is plain ASCII punctuation only.

| Banned | Use instead |
|--------|-------------|
| em-dash (`—`) and en-dash (`–`) | period, comma, or colon |
| curly/smart quotes (`'` `'` `"` `"`) | straight quotes (`'` `"`) |
| ellipsis (`…`) | three periods (`...`) |
| arrows (`→` `←`) | `->`, `<-`, or words ("then", "to") |
| bullets (`•` `·`) in prose | ASCII hyphen-space (`- `), and only for enumerated concrete items |
| math letters (Unicode 𝗯𝗼𝗹𝗱 / 𝑖𝑡𝑎𝑙𝑖𝑐) | normal text. Screen readers spell these letter by letter |

**Carve-outs:**
- Pictograph emojis (📅 ✅ 🚀) are technically accessible but absent from the user's real writing, skip them in customer-facing copy.
- German Umlaute (`ä ö ü ß`) are language characters, not decoration. Always preserve. See `prose-style.md` (German orthography).
- ASCII emoticons (`:)` `;)` `xD`) where a real Slack message would land them.
- Slack format quirks (incl. the `•` bullet the Slack API requires): see `slack-channel.md`.

## Sender identity

All h&w correspondence sent as: `Benedikt Stemmildt | hackers&wizards <benedikt@hackersandwizards.dev>` (default Gmail sender).
