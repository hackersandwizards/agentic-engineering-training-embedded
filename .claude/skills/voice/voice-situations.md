# Voice: Narrow Situations

Three narrow scenarios with specific voice rules. Load only when the situation fits.

## Internal coordination gaps: never expose

When a client-facing issue stems from an internal h&w gap (a session got booked outside the normal sales/billing flow, scope drifted, an internal handoff was missed): never write *"wir haben intern festgestellt"* or any phrasing that signals process trouble.

Instead:
1. Open with thanks or positive framing of whatever the client did. (*"danke, dass ihr den 4. Termin dazugebucht habt"*)
2. Ask the practical clarification question. (separate invoice? which month? same conditions?)
3. Skip the why.

**Failure mode if you expose the gap:** even genuine transparency about an internal gap reads as unprofessional and erodes trust. The fix happens internally; the client sees a clean, warm clarification.

**Scope:** applies when *we* are the source of the gap. When the *client* caused the issue, naming it and clarifying is fine.

## Spoken voice (Fathom transcripts -> written)

When converting the user's spoken words (Fathom transcripts, talks, recorded conversations) to written form, keep the user's energy and the building-thoughts-while-speaking flow. *"Ich denke ja immer beim Reden"*: that quality belongs in the written version too, lightly tightened.

**What to keep:**
- Specific examples and numbers: spoken specifics are the credibility.
- Triple-emphasis (*"sehr, sehr, sehr"*), self-corrections, asides: these are voice markers.
- Spoken *"ja"* or *"also"* often marks a transition: translate as paragraph breaks or short connectors.

**What to cut:**
- *"ähm"* and other hesitation fillers.
- *"vllt."* and *"halt"* on conversion to writing (filler per `prose-style.md`).
- Pure repetition without rhythm.

Conversion is mostly tightening, not voice translation. Goal: a written version that reads like an articulate email from the user, not a polished think-piece.

## Language detection (DE vs EN)

Pick the language by signal. User override always wins.

| Signal | Language |
|--------|----------|
| Thread / conversation already in German | German |
| Thread / conversation already in English | English |
| DACH region, German names, `.de` domain | German |
| International client, English-only thread | English |
| Mixed thread | match what the recipient used last |
| No prior history | infer from name, domain, location |

When the signal is ambiguous, default to English for international names and German for DACH names. If still uncertain, ask before drafting.
