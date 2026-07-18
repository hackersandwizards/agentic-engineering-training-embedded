# Prose Style: Bilingual (DE/EN)

Apply when drafting any prose a human will read: emails, proposals, posts, slides, README content, Slack messages, client docs. Skip for code, command output, raw data dumps, and quoted source material.

This file is the authority on sentence mechanics in authored prose (articles, posts, proposals, slides, docs). In relational prose (email, Slack, WhatsApp, DMs) `personal-voice.md` wins on warmth devices; everything else here (verbs, passive, concrete, orthography) still applies.

## North star

Schneider, Reiners, Strunk & White, and Orwell converge on the same craft: short sentences, strong verbs, concrete nouns, no filler. The DE/EN deltas are vocabulary, not principle. Apply both traditions; pick the language-specific examples below.

The goal: the reader gets the point fast and remembers it. Texts that feel **diskussionswürdig, klar, pointiert** earn it through mechanics, not adjectives.

## Sentence shape

- Long-form (proposals, posts, slides, articles, client docs): main clauses 15-20 words. Hard ceiling 26. Past 26, split, readers lose the subject.
- Email, Slack, chat: shorter. Average 8-12 words per sentence (German ~8-9, English ~11-12), the user's measured cadence. Mix short punches with the occasional 14-word sentence; don't stack staccato 5-word fragments. See the voice self-check in `SKILL.md`.
- One main idea per sentence. Subordinate clauses only when the relation is non-obvious from juxtaposition.
- Inserts (Einschübe / parentheticals): max 6 words or 12 syllables. Past that, the reader backtracks to the verb.
- Em-dashes are banned in customer-facing prose. When rewriting, replace with comma, parenthesis, or new sentence.

## Strong verbs over nominalizations

Schneider: "Weg mit den Adjektiven, her mit den Verben." Reiners catalogues this antipattern as *Hauptwörterei*: noun-stacking that freezes action into bureaucratic abstraction. Strunk's English mirror: "Use definite, specific, concrete language."

Trigger pattern: a noun ending in `-ung`, `-heit`, `-keit`, `-ion`, `-ität`, `-ismus` (DE) or `-tion`, `-ment`, `-ance`, `-ity` (EN) paired with a weak verb (*erfolgen, vornehmen, durchführen, perform, conduct, make, give*) is a *Streckverb* (stretched verb). Replace with the verb hidden inside the noun.

- DE: "zur Anwendung kommen" -> "anwenden". "Die Durchführung der Analyse erfolgt" -> "Wir analysieren". "Eine Entscheidung treffen" -> "entscheiden".
- EN: "make a decision" -> "decide". "perform an analysis of" -> "analyze". "give consideration to" -> "consider".

## Active voice as default

Passive hides the actor. In a consultancy that names sources for everything, the actor almost always matters.

- DE: "Es wird eine Entscheidung getroffen" -> "Das Team entscheidet."
- EN: "A decision was made" -> "The team decided."

Keep passive only when the actor is genuinely irrelevant (well-known generic process) or when foregrounding the object is the point ("The contract was signed yesterday": what matters is the contract, not the pen-holder).

## Concrete over abstract

Reiners: *anschaulicher Ausdruck*. Strunk: definite, specific, concrete. Same rule.

Replace vague quantifiers with the actual number, or cut the claim:
- "Wir verbessern die Performance deutlich" -> "Wir senken die Latenz von 800 auf 200 ms."
- "Significant productivity gains" -> "30 % weniger Tickets pro Sprint."

Banned modifiers without numbers: `deutlich, signifikant, erheblich, massiv, considerable, substantial, significant, dramatic`. Failure mode: these words signal corporate filler and the reader stops trusting the claim.

## Filler: cut on sight (authored prose)

These words almost always survive their own deletion. Test: read the sentence without the word; if the meaning holds, it was filler.

Epistemic markers (`I think`, `glaub ich`, `honestly`, `in my opinion`) carry stance and aren't filler.

**Relational-prose exception.** In email, Slack, and personal messages, Abtönungspartikel (`mal`, `einfach`, `doch`, `eh`) and softeners (`gern`, `vllt.`, `ggf.`) carry politeness and warmth: "Sagt einfach Bescheid" invites, "Sagt Bescheid" instructs. Keep them at the user's natural density (see `personal-voice.md`). The filler sentence-frames and EN connectors below stay banned everywhere.

DE: `eigentlich, durchaus, gewissermaßen, quasi, sozusagen, eben, halt, mal, ja, doch, wohl, schon, einfach, irgendwie, irgendwo, eventuell, vielleicht, dann, also, nun, nämlich, natürlich, übrigens, bekanntlich, tatsächlich`

EN: `actually, basically, essentially, really, quite, rather, somewhat, just, simply, sort of, kind of, very, totally, literally, obviously, of course, indeed, in fact, perhaps, maybe`

Filler sentence-frames (cut the frame, lead with the claim):
- DE: "Es ist festzustellen, dass ..." / "Es ist wichtig zu betonen, dass ..." / "Man kann sagen, dass ..." / "In diesem Zusammenhang ..."
- EN: "It should be noted that ..." / "It is important to mention that ..." / "One could argue that ..." / "In this context, it is worth noting ..."
- EN connectors: "Furthermore" / "Moreover" / "In conclusion". Cut these and start the new sentence with the claim.

## No throat-clearing openers

Lead with the claim, the conflict, or a concrete scene. Do not open with the year, a dictionary definition, a famous quote, or a generic state-of-the-world sentence, unless the relevance lands in the next clause.

Failure mode: openers like "In today's fast-paced world ..." or "Seit jeher beschäftigt die Menschheit ..." mark the writer as corporate, and the reader bails before the content arrives.

## German orthography

Always use proper German Umlaute and Sonderzeichen (ä, ö, ü, ß, Ä, Ö, Ü) in emails, messages, and all German text. Keep the original characters intact; ASCII fallbacks like `ae`, `oe`, `ue`, `ss` belong to legacy systems only. Ensure UTF-8 encoding. Example: `grüße`, not `gruesse`.

## Foreign words, jargon, Anglizismen

Use them when they do work the local language can't. Cut them when an everyday word means the same.

- DE: "agentic engineering" stays, field's term of art. "implementieren" when "umsetzen" works -> "umsetzen". "Performance" when "Geschwindigkeit" or "Latenz" works -> use the German.
- EN: "Schadenfreude" stays, no equivalent. "utilize" when "use" works -> "use".

Reiners over-prosecuted *Fremdwörter* on culturalist grounds. Modern application is functional, not nationalist: the test is reader comprehension, not linguistic purity.

## When the rule fights the meaning

Break any rule before producing something stilted, false, or dead. Orwell's sixth: "Break any of these rules sooner than say anything outright barbarous." A 27-word sentence that flows beats a 25-word sentence that limps.

These rules serve clarity. When following the rule reduces clarity, the rule loses.
