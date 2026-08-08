# Signature Phrases: The User's Real Vocabulary

Load when ghostwriting from a transcript, calibrating an article, blog, or talk that should feel
verbatim-his, or anchoring a draft that needs more voice depth than `personal-voice.md` provides.

The calibration anchors come from real sent mail, and the email exemplars are read from it live
rather than kept here. The slogan catalogue below
does not: everything from "Positioning and identity" downward scored **zero occurrences** in the
sampled corpus (28 of 520 meetings, 240 mails, 5,509 messages). **His meeting and mail vocabulary is
far plainer than the catalogue implies. Do not reach for a slogan when drafting.** Use the catalogue
to recognise his positioning, not to generate his sentences. Slogans attested in written material
live in `brand-vocabulary.md` instead.

## Calibration anchors

**Five sentences that are pure user voice:**

1. *"Bekommen wir alles hin."*
2. *"Profi. Pre-Mortem ist super geil! Danke dir [team member] :)"*
3. *"Hui. Den Termin hab ich total verpeilt weil er nicht im Kalender steht."*
4. *"Vermisse euch etwas :)"*
5. *"Wird sich zeigen. Nur schon mal als Info."*

A draft with lines like these in spirit sounds like him. A draft with zero lines like these sounds
like a consultant trained on his domain.

## Real email exemplars

Read them from Gmail; do not store them here. The mailbox holds every mail he has written,
unredacted, current, and addressed to the person actually being written to, which a frozen copy
here is none of. Before a draft that needs voice depth:

```bash
gws gmail users messages list --params '{"userId":"me","q":"in:sent -label:os/drafted to:ADDRESS","maxResults":5}'
gws gmail users messages get --params '{"userId":"me","id":"ID","format":"full"}'
```

Drop the `to:` term for the register rather than the relationship, and add a language term where the
draft is English. Read the new text above the quote header, not the quoted thread.

`-label:os/drafted` excludes the mail an agent drafted for him. Without it the corpus drifts into
the fleet's own output and the calibration ends up measuring itself.

## Positioning and identity

**Foundational reframes:**

- *"Agents sind keine AI. Sie sind Programme, die AI nutzen."* The foundational reframe for
  technical understanding.
- *"AI ist ein Amplifikator. Gute Architektur skaliert schneller, schlechte Architektur wird
  schneller schlechter."*
- *"AI amplifies what's already there. Good processes get better. Bad processes get worse faster."*
  English version.
- *"This isn't a tool rollout. It's a change management initiative."*
- *"It's not about using AI, it's about developing it as a colleague."*
- *"The problem isn't the AI assistant, it's the lack of context engineering practices."*
- *"Die Technologie ist eigentlich gar nicht das, was im Weg steht. Im Weg steht ist dieser Change in
  den Leuten."*
- *"Die echten Effizienzgewinne holt man in den Prozessen drumherum."*

**Definitive positioning statements:**

- *"Das ist nicht Vibe Coding... hier wird nichts gecodet und hier wird auch nichts gevibed."*
- *"Man kann mit dem AI-Thema unter dem Radar noch breitere organisatorische Veränderungen
  treiben."* AI as Trojan horse for org change.
- *"Only a team that delivers the assessment itself with AI has the credibility to judge AI
  readiness. Anything else is hearsay."*

**Origin:**

- *"Ich starte meine Story immer ganz gerne damit, dass ich 1999 den Computer von meinem Vater
  auseinandergebaut habe."* PC disassembly at age 9, Pentium 750MHz.
- *"The magic is real, it's just sufficiently advanced."*
- *"Reclaiming the magic in technology."*

## Methodology and craft

**Context engineering:**

- *"Context is everything"* / *"Kontext ist alles"*.
- *"Die Lösung muss eigentlich immer schon in dem sein, was ich dem LLM schicke."*
- *"The answer needs to be in the question."* English teaching version.
- *"70-80% preparation, 20-30% coding."* The context engineering ratio.
- *"Smart Zone / Dumb Zone"* with the 60% threshold: at 60% fill, quality degrades invisibly.
- *"Instructions-Last"* / *"Bare Metal starten"*: start with zero context, let the agent discover
  what it needs.

**Process patterns:**

- *"Research Plan Implement."* Fractal process pattern at every level: feature, story, task.
- *"Start simple. Observe. Refine."*
- *"Sprint 1-2: anstrengend. Sprint 3-4: breakeven. Sprint 5-6: schneller."* Realistic adoption
  timeline, prevents discouragement.
- *"CLAUDE.md files are guidelines, not guarantees. For critical safety, use environment
  controls."*
- *"Manufacturing pipeline"*: industrial metaphor for SDLC.
- *"Kein Bauchgefühl, sondern klare Werte."* Data over intuition for pilot decisions.

**Specs and deliverables:**

- *"Die User-Story ist ein durchlaufendes Ding für die Planung. Die Spezifikation beinhaltet das, was
  nachher wirklich daraus entstanden ist."*
- *"Ich hab von diesen 80 Seiten genau drei gelesen."* [client] procurement story; Claude Code
  generated *"die beste Ausschreibung, die sie je gesehen haben."*

## Sales, pricing, and demos

- *"One real team, one real story is enough."* N=1 proof for unlocking budget.
- *"You are in the top 1% who figure this out on their own."* Validation move for prospects who
  already practice context engineering.
- *"Wir sind ja nicht AWS oder Google."* Vendor-neutral positioning in enterprise sales.
- *"Ich will keinen Sales machen."* Boundary-setting in process workshops.
- *"Es soll ja auch für euch wertschöpfend sein."*
- *"Supply-mäßig können wir das liefern."* Supply-side confidence when client scope expands.
- *"Ich habe das alles transparent gemacht. Bin da nicht so wie andere."* Radical pricing
  transparency as a value.

**Live-demo framing:**

- *"Da siehst du richtig, wie sich deren Gesichtsausdruck langsam verändert."*
- *"Du darfst nicht die Erwartung haben, dass der Agent One-Shot-mäßig ein geiles Ergebnis
  produziert, sondern das ist halt wie ein Mensch."* Humanizing agents, the anthropomorphic mapping
  from `postures.md` posture 5.
- *"The developer was sleeping while the agent shipped."*

## Diagnostic, conviction, and self-awareness

**Diagnostic phrases:**

- *"You have a pressure cooker situation."* Diagnosing the top-down/bottom-up gap.
- *"Productivity illusion"*: what false metrics produce.

**Self-deprecation and credibility:**

- *"Ich habe keine Ahnung von AI."* Disarming self-deprecation before pivoting to process
  expertise.
- *"Ich mach mir immer Sorgen, dass die alles schon können. Tun sie nie."*
- *"Ich denke ja immer beim Reden."*
- *"Unser FastAPI Repository ist natürlich super ordentlich."* Self-deprecating humor about training
  repos being unrealistically clean.
- *"Ehrlicherweise"*: real but far rarer than earlier guidance claimed. 44 occurrences, 0.36 per
  1000 words, roughly 39x rarer than `also`. It is a marker, not a tic. He is self-aware about it:
  *"ich benutze das Wort ehrlicherweise gerade ehrlicherweise relativ viel."*

**Blunt tool assessments:**

- *"Politisch korrekt ist der nicht gut, politisch unkorrekt ist der einfach scheisse."* On Copilot.
- *"Alle Menschen, die VSCode nutzen, sind mir grundsaetzlich erstmal suspekt."* JetBrains loyalty
  as identity marker.
- *"Man braucht die IDE irgendwie nicht mehr so richtig."*

These are jokes about tools, not a model for disagreeing with a person. **How he actually pushes
back is measured in `postures.md` posture 2**: agreement token first when live, bare negation first
in writing. Nothing in this file describes a pushback shape.

## Vision and empowerment

- *"180 Agenten-Teams hinter sich."* Vision of 2-3 person teams backed by hundreds of agent
  instances.
- *"Our job changes from writing code and reviewing code to reading what the AI produces."*
- *"Ich glaube, es macht wirklich total viel Sinn, wenn ihr einfach selber auch erstmal viel
  ausprobiert."* Empowerment through withdrawal.
- *"Defaults eines Modells sind quasi User-Feedback."*

## Qualified claims

- *"That works great for [X], but if you're [Y], you need something different."*
- *"SPAs sind legacy"* (in the right context).
- *"Microservices verhindern Geschwindigkeit"* (in specific situations).

These read as conviction in delivery; in writing, attach the *"in the right context"* qualifier so
they don't read as absolutist.
