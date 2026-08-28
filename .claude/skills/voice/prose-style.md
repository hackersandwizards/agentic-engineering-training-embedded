# Prose Style: Bilingual (DE/EN)

Apply when drafting any prose a human will read: emails, proposals, posts, slides, README content,
Slack messages, client docs. Skip for code, command output, raw data dumps, and quoted source
material.

This file is the authority on sentence mechanics in **authored** prose (articles, posts, proposals,
slides, docs). In **relational** prose (email, Slack, WhatsApp, DMs) `personal-voice.md` wins on
warmth devices and owns the measured sentence and message lengths; everything else here (verbs,
passive, concrete, orthography) still applies.

## North star

Short sentences, strong verbs, concrete nouns, no filler. The DE/EN deltas are vocabulary, not
principle. Texts that feel **diskussionswürdig, klar, pointiert** earn it through mechanics, not
adjectives.

## Sentence shape

- Long-form (proposals, posts, slides, articles, client docs): main clauses 15-20 words. Hard ceiling
  26. Past 26, split, readers lose the subject.
- Email, Slack, chat: much shorter, and the numbers are measured, not estimated. Take them from
  `personal-voice.md`, "The hard numbers", and do not average upward toward the long-form range.
- One main idea per sentence. Subordinate clauses only when the relation is non-obvious from
  juxtaposition.
- Inserts (Einschübe, parentheticals): max 6 words or 12 syllables. Past that, the reader backtracks
  to the verb.

## Strong verbs over nominalizations

Trigger pattern: a noun ending in `-ung`, `-heit`, `-keit`, `-ion`, `-ität`, `-ismus` (DE) or
`-tion`, `-ment`, `-ance`, `-ity` (EN) paired with a weak verb (*erfolgen, vornehmen, durchführen,
perform, conduct, make, give*) is a *Streckverb* (stretched verb). Replace with the verb hidden
inside the noun.

- DE: "zur Anwendung kommen" -> "anwenden". "Die Durchführung der Analyse erfolgt" -> "Wir
  analysieren". "Eine Entscheidung treffen" -> "entscheiden".
- EN: "make a decision" -> "decide". "perform an analysis of" -> "analyze". "give consideration to"
  -> "consider".

## Active voice as default

Passive hides the actor. In a consultancy that names sources for everything, the actor almost always
matters.

- DE: "Es wird eine Entscheidung getroffen" -> "Das Team entscheidet."
- EN: "A decision was made" -> "The team decided."

Keep passive only when the actor is genuinely irrelevant, or when foregrounding the object is the
point ("The contract was signed yesterday": what matters is the contract, not the pen-holder).

## Concrete over abstract

Replace vague quantifiers with the actual number, or cut the claim:

- "Wir verbessern die Performance deutlich" -> "Wir senken die Latenz von 800 auf 200 ms."
- "Significant productivity gains" -> "30 % weniger Tickets pro Sprint."

Banned modifiers without numbers: `deutlich, signifikant, erheblich, massiv, considerable,
substantial, significant, dramatic`. Failure mode: the reader reads corporate filler and stops
trusting the claim.

## Three or more parties: name each one

When a partner, a subcontractor, and an end client all appear in the same message, `wir` / `uns` /
`we` reads as any sender-side combination. Write the company name for each party and keep `wir` only
where the recipient is inside it. Sweep the finished draft pronoun by pronoun, and use the shorthand
the counterparty already uses in the thread.

- "Daraus machen wir einen Festpreis" -> "Daraus macht h&w einen Festpreis"
- Joint, so it stays: "Den Überschuss teilen wir."

Failure mode: the reader assigns cost, risk, and upside to the wrong party, and the ambiguity sits
exactly where the money is.

## Filler: cut on sight (authored prose)

These words almost always survive their own deletion. Test: read the sentence without the word; if
the meaning holds, it was filler.

Epistemic markers (`I think`, `glaub ich`, `I'm not sure`) carry stance and aren't filler.

**Relational-prose exception.** In email, Slack, and personal messages, Abtönungspartikel (`mal`,
`einfach`, `doch`, `eh`, `schon`, `halt`) and softeners (`gern`, `vllt.`, `ggf.`) carry politeness
and warmth: "Sagt einfach Bescheid" invites, "Sagt Bescheid" instructs. Keep them at his measured
density (`personal-voice.md`). The filler sentence-frames and EN connectors below stay banned
everywhere.

DE: `eigentlich, durchaus, gewissermaßen, quasi, sozusagen, eben, halt, mal, ja, doch, wohl, schon,
einfach, irgendwie, irgendwo, eventuell, vielleicht, dann, also, nun, nämlich, natürlich, übrigens,
bekanntlich, tatsächlich`

EN: `actually, basically, essentially, really, quite, rather, somewhat, just, simply, sort of, kind
of, very, totally, literally, obviously, of course, indeed, in fact, perhaps, maybe`

Filler sentence-frames (cut the frame, lead with the claim):

- DE: "Es ist festzustellen, dass ..." / "Es ist wichtig zu betonen, dass ..." / "Man kann sagen,
  dass ..." / "In diesem Zusammenhang ..."
- EN: "It should be noted that ..." / "It is important to mention that ..." / "One could argue that
  ..." / "In this context, it is worth noting ..."
- EN connectors: "Furthermore" / "Moreover" / "In conclusion". Cut these and start the new sentence
  with the claim.

## No throat-clearing openers

Lead with the claim, the conflict, or a concrete scene. Do not open with the year, a dictionary
definition, a famous quote, or a generic state-of-the-world sentence, unless the relevance lands in
the next clause.

Failure mode: "In today's fast-paced world ..." or "Seit jeher beschäftigt die Menschheit ..." marks
the writer as corporate and the reader bails before the content arrives.

## Spoken to written

Converting his spoken words (Fathom transcripts, talks, recorded conversations) to written form is
mostly tightening, not translation. Keep the energy and the building-thoughts-while-speaking flow.
Goal: a written version that reads like an articulate email from him, not a polished think-piece.

**Keep:** specific examples and numbers (the spoken specifics are the credibility), self-corrections,
asides, and the inline assent tag (`ne?`, `right?`), which becomes a short confirming clause at the
end of a claim (`postures.md` posture 5).

**Cut.** These are the real spoken filler load, measured: `sozusagen` (621), `irgendwie` (537),
`kind of` (504), `halt`, plus `ähm` and other hesitation fillers, and pure repetition without
rhythm. Cutting them is most of the work.

**Convert:** spoken `ja` or `also` usually marks a transition. Render as a paragraph break or a short
connector, not as a word.

Triple-emphasis (*"sehr, sehr, sehr"*) is rare, one literal occurrence in the whole spoken corpus.
Do not reproduce it as a voice marker.

## Language detection (DE vs EN)

Pick the language by signal. User override always wins.

**A stated language outranks every signal below.** Where the record for the recipient, their team,
or their customer states a language, that value decides. Inference never overrides it, and the table
applies only where no Company OS record governs the language. Where one governs it and states
nothing, that silence is not this table's to fill.

| Signal | Language |
|--------|----------|
| Thread / conversation already in German | German |
| Thread / conversation already in English | English |
| DACH region, German names, `.de` domain | German |
| International client, English-only thread | English |
| Mixed thread | match what the recipient used last |
| No prior history | infer from name, domain, location |

When the signal is ambiguous, default to English for international names and German for DACH names.
If still uncertain, write English: a German reader handling an English mail is the smaller failure.

## German orthography

Always use proper German Umlaute and Sonderzeichen (ä, ö, ü, ß, Ä, Ö, Ü), never ASCII fallbacks like
`ae`, `oe`, `ue`, `ss`. Example: `grüße`, not `gruesse`. His short forms are not typos and stay:
`grad`, `vllt`, `nen`, `gern` (`personal-voice.md`).

## Foreign words, jargon, Anglizismen

Use them when they do work the local language can't. Cut them when an everyday word means the same.

- DE: "agentic engineering" stays, field's term of art. "implementieren" when "umsetzen" works ->
  "umsetzen". "Performance" when "Geschwindigkeit" or "Latenz" works -> use the German.
- EN: "Schadenfreude" stays, no equivalent. "utilize" when "use" works -> "use".

The test is reader comprehension, not linguistic purity.

## When the rule fights the meaning

These rules serve clarity. Break any of them before producing something stilted, false, or dead. A
27-word sentence that flows beats a 25-word sentence that limps.
