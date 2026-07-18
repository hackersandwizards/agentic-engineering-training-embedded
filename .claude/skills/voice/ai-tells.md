# AI tells

A detector list, not a positive rule. It catches AI tells; the writing rules themselves live in `prose-style.md`. Run the draft against this file after the four base layers, asking of each paragraph only: "would a reader looking for AI output flag this?" Rewrite anything that triggers without the offending pattern, not around it. One instance is usually enough to flip a paragraph's register from "the user wrote this" to "the user's bot wrote this". DE and EN both; bans apply regardless of punctuation or surface variation.

## 1. Structural patterns

The single highest-signal category. These shape sentences, not just word choice, so they survive paraphrasing.

### Contrastive reframe ("not just X, it's Y")

The #1 catalogued LLM tell: it feigns insight by negating a strawman. Uses in U.S. corporate documents roughly doubled in both 2024 and 2025.

| Banned | Use instead |
|--------|-------------|
| "It's not just X, it's Y" | name Y directly |
| "It's not X, it's Y" | drop the negation, lead with the claim |
| "We don't just X, we Y" | "We Y" |
| "Not a trend, an epidemic" / "Not a tool, a partner" | give the concrete claim without the contrast frame |
| "X isn't evolving, it's accelerating" (any pivot punctuation) | same rule, banned in all forms |
| DE: "Nicht nur X, sondern Y" / "Das ist kein X, das ist ein Y" | nenn Y direkt |

### Negative parallelism ("no X, no Y, just Z")

| Banned | Use instead |
|--------|-------------|
| "No fluff, no jargon, just results" | name the actual result |
| "Not slower, not cheaper, but smarter" | drop the triplet, make one concrete claim |
| DE: "Kein X, kein Y, sondern Z" | same rule |

### Rule of three (forced triplets)

Triplet adjectives, triplet noun phrases, triplet parallel clauses applied regardless of necessity. Signals statistical pattern matching, not earned rhythm.

- Banned: "fast, reliable, and secure" / "build, measure, learn" / "clarity, speed, focus" when they are not each essential.
- Use instead: pick the one that matters and cut the rest. If three concepts genuinely belong, break the rhythm: vary clause length so it doesn't read as a triplet.

### Aphorism stacking

Multiple short declaratives in a row, each pretending to be wisdom.

- Banned: "Clarity is speed. Less is more. The simplest version wins."
- Use instead: one concrete observation tied to a specific situation. If there are three, separate them with context, don't stack.

### Announced count / enumerated preview

Naming how many points are coming before making them. The model commits to a number before the content earns it, so the count reads as scaffolding.

| Banned | Use instead |
|--------|-------------|
| "Three things I'd push on." | lead with the first point, let the list reveal its own length |
| "Two things to note:" | drop the preamble, state the first thing |
| "A few thoughts:" / "Here are some reasons:" | start with the thought |
| DE: "Drei Dinge dazu:" / "Zwei Punkte:" | dieselbe Regel |

Exception: a count the argument depends on ("only two of the five survive") stays.

### Soft-challenge verbs ("push on", "poke at")

Hedged consultant-speak that softens a disagreement into a gesture. Signals an LLM smoothing a critique rather than stating it.

| Banned | Use instead |
|--------|-------------|
| "Things I'd push on" / "One thing I'd push back on" | name the disagreement directly: "Two of these contradict each other." |
| "I'd poke at this" / "worth pressing on" | "This is wrong because..." or "This overstates itself." |
| DE: "Hier würde ich nachhaken" / "Daran würde ich rütteln" | sag den Einwand direkt |

### Elegant variation (synonym hopscotch)

LLM training penalizes repetition, so models swap synonyms for the same referent. Reads as labored.

- Banned: "Yankilevsky... the non-conformist artist... their creative output...".
- Use instead: repeat the noun. Plain repetition reads as confident.

### Generic temporal/landscape opener

| Banned | Use instead |
|--------|-------------|
| "In today's fast-paced landscape..." | drop the frame, open on the claim |
| "In a world where..." | open on the concrete situation |
| "Right now, X is changing faster than..." | name the change |
| DE: "In der heutigen Zeit..." / "In einer Welt, in der..." | dieselbe Regel |

### The four-beat AI Sentence DNA

Bloomberry's structural finding across ChatGPT, Claude, Gemini, open-source models:

1. Opening: framing claim or landscape statement
2. Expansion: elaboration or supporting evidence
3. Contrast: reframe or tension signal (but / however / it's not just)
4. Resolution: takeaway, imperative, or call to action

When a paragraph follows this skeleton end-to-end, the reader clocks it as AI regardless of the words. Rewrite by:
- Cutting the opening landscape claim. Start at the expansion.
- Removing the contrast pivot in the middle. The claim stands without it.
- Cutting the closing imperative unless it names a specific next step.

### Crutch metaphors

- Banned: "load-bearing" ("load-bearing skill / line / assumption / convention"). Overused AI metaphor, reads as a tell within seconds.
- Use instead: name what it does, "critical", "the part the argument rests on", "the one that matters", "central". DE: "entscheidend" / "trägt das Argument", nicht "load-bearing".

## 2. Opener / hook patterns

Bloomberry catalogues 17 LLM opener hooks. The most common, banned in all forms:

| Pattern | Banned example | Use instead |
|---------|----------------|-------------|
| Curiosity hook | "Have you ever wondered..." | name the actual question |
| Candor opener | "Let's be honest..." | be honest without announcing it |
| Reveal setup | "Here's the thing..." | state the thing |
| Rhetorical-question challenge | "What if the way we think about X is wrong?" | make the claim directly |
| Contrarian opener | "Most people believe X. They're wrong." | argue the position without the binary |
| Statistic opener | "Studies show that X percent of teams..." | name the study; cite once, in body |
| Empathy opener | "If you've ever struggled with..." | open on a concrete moment |
| Direct imperative pair | "Stop doing X. Start doing Y." | argue the change instead of commanding it |
| Confession opener | "I used to think X. I was wrong." | tell the actual story, including the change |
| Urgency frame | "The window for X is closing." | name the deadline or cut the urgency |
| Paradox opener | "The more you try to X, the less Y you get." | drop the paradox framing |
| Community segmentation | "Whether you're a founder, a marketer, or a..." | address one audience at a time |

## 3. Transition / bridge fillers

Sentence connectors that pad without adding content. Different from buzzwords (which are nouns/verbs); these are linkers.

| Category | Banned | Use instead |
|----------|--------|-------------|
| Summary | "at the end of the day", "in a nutshell", "ultimately" | drop the bridge, the sentence carries itself |
| Restatement | "in other words", "the reality is", "to be clear" | if restatement is needed, the first version was wrong, rewrite it |
| Topic-pivot | "at its core", "when it comes to" | name the topic directly |
| Contrast | "on the other hand", "that said", "at the same time" | "but" or a period |
| Hedge | "it's worth noting", "needless to say", "moving forward" | if it's worth noting, just note it |
| DE | "letzten Endes", "im Grunde", "im Kern", "in der Tat", "nichtsdestotrotz" | dieselbe Regel |

## 4. Copula and verb dodging

Subtle but high-signal. LLMs disproportionately avoid plain "is" and "has".

| Banned | Use instead |
|--------|-------------|
| "X serves as a Y" | "X is a Y" |
| "X stands as a Y" | "X is a Y" |
| "X represents a Y" | "X is a Y" |
| "X marks a Y" | "X is a Y" or name the event |
| "X features Y" | "X has Y" |
| "X offers Y" | "X has Y" or "X gives Y" |
| "X boasts Y" | "X has Y" |
| DE: "X fungiert als Y", "X stellt ein Y dar" | "X ist ein Y" |

## 5. Formatting tics

### Title case in headings

LLMs default to Title Case Like This. Wikipedia and most modern style guides use sentence case. h&w voice uses sentence case throughout.

- Banned: "Impact of Technology and Digitalization"
- Use instead: "Impact of technology and digitalization"

### Excessive boldface

Every key term mechanically bolded, often as inline-header lists.

- Banned: "**Context engineering (CE):** the practice of structuring..."
- Use instead: bold sparingly; never as a substitute for actual headings.

### Inline-header vertical lists

"**Term:** description" pattern repeated as a list. Reads as slide-deck output, not prose.

- Banned:
  ```
  - **Speed:** ships faster
  - **Quality:** fewer bugs
  - **Joy:** developers stay
  ```
- Use instead: full sentences, or a real two-column table if the items are genuinely parallel.

### Emoji as section markers

Banned: 🚀 / 💡 / 🔍 / ⚠️ / ✅ as headings or bullets in customer-facing prose.
