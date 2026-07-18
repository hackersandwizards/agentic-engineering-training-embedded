---
name: voice
description: >-
  MUST be loaded before drafting, writing, composing, editing, or rewriting any human-readable prose that represents h&w or the user: emails, replies, Slack messages, WhatsApp and other personal messages, LinkedIn posts, proposals, quotes, talks, abstracts, speaker outreach, client comms, blog posts, articles, headlines, captions, slide decks, README copy, announcements, summaries, documentation prose, FAQs, surveys, notes for review. Skip only for code, code comments, command output, raw data, internal commit messages, log lines, and machine-readable config.
allowed-tools: Read, Glob, Grep, Bash
---

# Voice: Layered Stack

Everything needed to draft prose that represents h&w and the user.

## How to use

1. **Pick layers by situation.** Drafting prose -> all four base layers. Cold pitch -> add `pitch-framework.md`. Self-intro -> add `intro-framework.md`. Slack -> add `slack-channel.md`. Need verbatim phrases, competitive frame, or LLM-rewrite examples -> add `brand-vocabulary.md`.
2. **Pick the register.** *Relational* (email, Slack, WhatsApp, DMs: a person answers): connection first; `personal-voice.md` wins conflicts, warmth devices (Konjunktiv, Abtönungspartikel, `gern`, wishes, `:)`) stay at natural density. *Authored* (articles, LinkedIn posts, proposals, slides, docs: an audience reads): compression first; `prose-style.md` wins on sentence mechanics (length, shape, filler).
3. **Conflicts: specificity wins, then the register's lead file.** Channel beats brand/personal where it explicitly carves out (Slack format quirks live in `slack-channel.md`).
4. **Rules serve clarity.** `prose-style.md` ends with Orwell's sixth: break any rule before barbarism. When following the rule reduces clarity, the rule loses.

## The four base layers (apply in order)

Each layer constrains the next; the more concrete rule beats the more abstract one. Layers 1-3 are positive (write *from* them). Layer 4 is a filter (check *against* it after drafting).

| Layer | File | Owns |
|-------|------|------|
| 1. Brand | `brand-voice.md` | h&w-as-a-company: positioning principles, canonical banned-words list, performance-language standards, banned Unicode/style, Schwartz awareness-stage messaging, audience, sender identity |
| 2. The user's voice | `personal-voice.md` | The user specifically: rhythm, hedges, Konjunktiv, openings/closings, channel calibration table, anti-patterns, inline verbatim quotes. Leads in relational prose; defers to `prose-style.md` on sentence mechanics in authored prose. |
| 3. Prose | `prose-style.md` | Sentence mechanics (DE/EN): short sentences, strong verbs over nominalizations, no filler, concrete over abstract, German orthography (UTF-8 Umlaute). Authority on mechanics in authored prose. Schneider, Reiners, Strunk & White, Orwell. |
| 4. AI-tells filter | `ai-tells.md` | Pure detector list of sentence structures, openers, transitions, copula dodges, and formatting tics that mark prose as LLM-generated. Run the draft against it after layers 1-3 and rewrite anything that triggers. Writing rules themselves live in `prose-style.md`. |

## Channel overlays: apply when the channel matches

Layered on top of the base rules.

| File | Channel | Owns |
|------|---------|------|
| `slack-channel.md` | Slack via the MCP tool | Markdown quirks (`**bold**`, `•` bullets, 4-space code), length tiers per message type, greeting/closing rules |

Other channels (email, LinkedIn, speaker outreach) have no unique mechanics; voice + prose is enough. Add a new channel rule only when the platform imposes format constraints.

## Scaffold overlays: apply when the situation matches

Pitch arcs, intro structures, content formulas. Layered on top of voice + channel.

| File | Situation | Owns |
|------|-----------|------|
| `pitch-framework.md` | Cold pitch, proposal, talk opener, sales arc | CAPSTONE: Clarity, Authority, Problem, Solution, The-Why, Opportunity, Next-step, Essence (Daniel Priestley methodology) |
| `intro-framework.md` | 30-second self-introduction at networking, conferences, podcasts | NSFAG: Name, Same, Fame, Aim, Game (Daniel Priestley methodology) |
| `content-formula.md` | Post-length content: LinkedIn essays, blog articles, talk arcs | The user's formula: Hook, Story, Question, Insight, Impact, Adventure |
| `negotiation.md` | Pricing pushback, advisor/partner setup, speaker fees, training-scope discussions, mentoring scope creep, asking for visibility/intros/access | Tactical empathy, interest-based negotiation, mutual-gain framing, calibrated questions, radical-honesty moves, h&w-specific situations. Voss + Harvard distilled to the user's phrasings (DE). |

## On-demand reference: load for deep calibration

| File | Purpose |
|------|---------|
| `signature-phrases.md` | The user's verbatim phrases: real lines from training, sales, talks, Slack, plus three email exemplars (peer-warm DE, business-warm EN, candid-logistics DE). Use when ghostwriting from a transcript or anchoring a draft that needs more voice depth than `personal-voice.md` provides. |
| `brand-vocabulary.md` | Verbatim service offerings, value-prop phrases, approved adjectives, the full competitive-positioning frame, the approved performance-language patterns, and on-brand-vs-off-brand worked rewrites. Use when actively positioning in proposals or sales decks, citing numbers, or rewriting LLM output to on-brand. |
| `voice-situations.md` | Three narrow scenarios: never-expose internal coordination gaps (when an h&w-side issue lands client-facing), spoken-to-written conversion (Fathom transcripts -> text), and DE/EN language detection. Load only when one of those fits. |

## Voice self-check: does this read as the user?

After drafting personal prose (email, Slack, LinkedIn, blog, talk; not technical docs or code), check the draft against these targets and against the three exemplar emails in `signature-phrases.md`. The numbers are measured from the user's real sent mail (79 emails 2025; re-validated on 445 sent mails Jun-Jul 2026), not guessed.

- **Sentence length.** Sentence mechanics live in `prose-style.md`; in authored prose it is the authority when a number here and a rule there disagree.
- **Greeting.** `Moin` / `Moin {Name}` / `Moin zusammen` / `Moin ihr beiden`, or none for a continuing thread or a quick logistics note. `Hey {Name}` works for casual peers. Never `Hallo`, `Dear`, or `Sehr geehrter`.
- **Sign-off.** `LG` (DE) / `Cheers` (EN), then `/bene` on its own line below it. Warm variant: `LG und {Wunsch}` (`LG und schönes Wochenende`). `BG` / `Stemmildt` for authorities, vendors, banks. Short logistics replies may skip the sign-off.
- **Punctuation.** No em-dashes, no semicolons. Parentheses are fine in moderation (the user uses them). Exclamation marks, `:)` `;)` `:P` `:D`, and ALLCAPS for emphasis are natural.
- **Cadence.** One or two sentences per paragraph, blank lines between. Rhythm comes from white space, not bold.

Don't distort the text to hit a number. These describe the user's real range; when the meaning needs a longer sentence, write it.
