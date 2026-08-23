---
name: voice
description: >-
  MUST be loaded before drafting, writing, composing, editing, or rewriting any human-readable prose that represents h&w or the user: emails, replies, Slack messages, WhatsApp and other personal messages, LinkedIn posts, proposals, quotes, talks, abstracts, speaker outreach, client comms, blog posts, articles, headlines, captions, slide decks, README copy, announcements, summaries, documentation prose, FAQs, surveys, notes for review. Skip only for code, code comments, command output, raw data, internal commit messages, log lines, and machine-readable config.
allowed-tools: Read, Glob, Grep, Bash
---

# Voice: Postures over a Layered Stack

## How to use

1. **Pick the register.** *Relational* (email, Slack, WhatsApp, DMs: a person answers): connection first; `personal-voice.md` wins conflicts, warmth devices (Konjunktiv, Abtönungspartikel, `gern`, `:)`) stay at natural density. *Authored* (articles, LinkedIn posts, proposals, slides, docs: an audience reads): compression first; `prose-style.md` wins on sentence mechanics (length, shape, filler).
2. **Name the posture.** Relational prose always has one. `postures.md` is the primary axis: it decides length, the opening and closing move, directness, and the verbatim phrasings available. Load it before writing a word. Authored prose has no posture; use a scaffold overlay instead.
3. **Apply the four base layers in order** (below), then the overlays the situation calls for. Cold pitch -> `pitch-framework.md`. Self-intro -> `intro-framework.md`. Slack -> `slack-channel.md`. Verbatim phrases, competitive frame, or LLM-rewrite examples -> `brand-vocabulary.md`.
4. **Conflicts: specificity wins, then the register's lead file.** Posture beats every layer on length, openings, closings, and directness. Layers beat the posture on everything else. Channel mechanics beat both where they explicitly carve out (Slack format quirks live in `slack-channel.md`).

## The primary axis

| File | Owns |
|------|------|
| `postures.md` | The eight measured situational registers of relational prose: quick reply, decision/pushback, delegation/ask, repair, teaching, scheduling, intro, status update. Length, opening and closing moves, directness, verbatim phrasings. Also marks what the evidence does not cover. |

## The four base layers (apply in order)

Each layer constrains the next; the more concrete rule beats the more abstract one. Layers 1-3 are positive (write *from* them). Layer 4 is a filter (check *against* it after drafting).

| Layer | File | Owns |
|-------|------|------|
| 1. Brand | `brand-voice.md` | h&w-as-a-company: positioning, banned words, performance-language, banned Unicode, awareness-stage messaging, audience, sender identity, client naming |
| 2. The user's voice | `personal-voice.md` | The user specifically, and only what holds across every posture: character, the measured hard numbers, greeting and sign-off, orthography and particles, emoji, anti-patterns. Leads in relational prose; defers to `prose-style.md` on sentence mechanics in authored prose. |
| 2b. Stefan's voice | `stefan-voice.md` | Stefan specifically: his greeting, sign-off and address form, which differ from the other founder's. Read it instead of `personal-voice.md` when the mail is signed by Stefan; who signs comes from the record's `assignee`. |
| 3. Prose | `prose-style.md` | Sentence mechanics (DE/EN) and German orthography. Authority on mechanics in authored prose. |
| 4. AI-tells filter | `ai-tells.md` | Detector list of structures, openers, transitions, copula dodges, and formatting tics that mark prose as LLM-generated. Run the draft against it after layers 1-3. |

## Channel overlays: apply when the channel matches

| File | Channel | Owns |
|------|---------|------|
| `slack-channel.md` | Slack via the MCP tool | Markdown quirks and Slack-only conventions |

Email, LinkedIn and Slack each have their own skill that owns the channel's mechanics and
delivery. Load it alongside voice.

## Scaffold overlays: apply when the situation matches

| File | Situation | Owns |
|------|-----------|------|
| `pitch-framework.md` | Cold pitch, proposal, talk opener, sales arc | CAPSTONE: Clarity, Authority, Problem, Solution, The-Why, Opportunity, Next-step, Essence. Scaffold only, no measured evidence behind it |
| `intro-framework.md` | 30-second self-introduction at networking, conferences, podcasts | NSFAG: Name, Same, Fame, Aim, Game |
| `content-formula.md` | Post-length content: LinkedIn essays, blog articles, talk arcs | Hook, Story, Question, Insight, Impact, Adventure |
| `negotiation.md` | Pricing pushback, advisor/partner setup, speaker fees, training-scope discussions, mentoring scope creep, asking for visibility/intros/access | Tactical empathy, calibrated questions, mutual-gain framing, h&w-specific situations |

## On-demand reference: load for deep calibration

| File | Purpose |
|------|---------|
| `signature-phrases.md` | The user's measured calibration anchors, how to pull real email exemplars from his mailbox, and his spoken slogan catalogue. Use when ghostwriting from a transcript or anchoring a draft that needs more voice depth than `personal-voice.md` provides. The slogan catalogue is unverified in conversation: read it to recognise his positioning, not to generate his sentences. |
| `brand-vocabulary.md` | Verbatim offerings and value-props, written positioning vocabulary (slogans attested in posts and the handbook), the competitive-positioning frame, approved performance-language patterns, on-brand-vs-off-brand rewrites. Use when positioning in proposals or sales decks, citing numbers, or rewriting LLM output to on-brand. |
