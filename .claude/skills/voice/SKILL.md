---
name: voice
description: >-
  MUST be loaded before drafting, writing, composing, editing, or rewriting any human-readable prose that represents h&w or the user: emails, replies, Slack messages, WhatsApp and other personal messages, LinkedIn posts, proposals, quotes, talks, abstracts, speaker outreach, client comms, blog posts, articles, headlines, captions, slide decks, README copy, announcements, summaries, documentation prose, FAQs, surveys, notes for review. Skip only for code, code comments, command output, raw data, internal commit messages, log lines, and machine-readable config.
allowed-tools: Read, Glob, Grep, Bash
---

# Voice: Layered Stack

## How to use

1. **Pick layers by situation.** Drafting prose -> all four base layers. Cold pitch -> add `pitch-framework.md`. Self-intro -> add `intro-framework.md`. Slack -> add `slack-channel.md`. Need verbatim phrases, competitive frame, or LLM-rewrite examples -> add `brand-vocabulary.md`.
2. **Pick the register.** *Relational* (email, Slack, WhatsApp, DMs: a person answers): connection first; `personal-voice.md` wins conflicts, warmth devices (Konjunktiv, Abtönungspartikel, `gern`, wishes, `:)`) stay at natural density. *Authored* (articles, LinkedIn posts, proposals, slides, docs: an audience reads): compression first; `prose-style.md` wins on sentence mechanics (length, shape, filler).
3. **Conflicts: specificity wins, then the register's lead file.** Channel beats brand/personal where it explicitly carves out (Slack format quirks live in `slack-channel.md`).

## The four base layers (apply in order)

Each layer constrains the next; the more concrete rule beats the more abstract one. Layers 1-3 are positive (write *from* them). Layer 4 is a filter (check *against* it after drafting).

| Layer | File | Owns |
|-------|------|------|
| 1. Brand | `brand-voice.md` | h&w-as-a-company: positioning, banned words, performance-language, banned Unicode, awareness-stage messaging, audience, sender identity |
| 2. The user's voice | `personal-voice.md` | The user specifically: character, warmth devices, openings and closings, channel calibration, anti-patterns. Leads in relational prose; defers to `prose-style.md` on sentence mechanics in authored prose. |
| 3. Prose | `prose-style.md` | Sentence mechanics (DE/EN) and German orthography. Authority on mechanics in authored prose. |
| 4. AI-tells filter | `ai-tells.md` | Detector list of structures, openers, transitions, copula dodges, and formatting tics that mark prose as LLM-generated. Run the draft against it after layers 1-3. |

## Channel overlays: apply when the channel matches

| File | Channel | Owns |
|------|---------|------|
| `slack-channel.md` | Slack via the MCP tool | Markdown quirks, length tiers per message type |

Other channels (email, LinkedIn, speaker outreach) have no unique mechanics; voice + prose is enough.

## Scaffold overlays: apply when the situation matches

| File | Situation | Owns |
|------|-----------|------|
| `pitch-framework.md` | Cold pitch, proposal, talk opener, sales arc | CAPSTONE: Clarity, Authority, Problem, Solution, The-Why, Opportunity, Next-step, Essence |
| `intro-framework.md` | 30-second self-introduction at networking, conferences, podcasts | NSFAG: Name, Same, Fame, Aim, Game |
| `content-formula.md` | Post-length content: LinkedIn essays, blog articles, talk arcs | Hook, Story, Question, Insight, Impact, Adventure |
| `negotiation.md` | Pricing pushback, advisor/partner setup, speaker fees, training-scope discussions, mentoring scope creep, asking for visibility/intros/access | Tactical empathy, calibrated questions, mutual-gain framing, h&w-specific situations |

## On-demand reference: load for deep calibration

| File | Purpose |
|------|---------|
| `signature-phrases.md` | The user's verbatim phrases and three email exemplars. Use when ghostwriting from a transcript or anchoring a draft that needs more voice depth than `personal-voice.md` provides. |
| `brand-vocabulary.md` | Verbatim offerings and value-props, the competitive-positioning frame, approved performance-language patterns, on-brand-vs-off-brand rewrites. Use when positioning in proposals or sales decks, citing numbers, or rewriting LLM output to on-brand. |
| `voice-situations.md` | Three narrow scenarios: internal coordination gaps, spoken-to-written conversion, DE/EN language detection. Load only when one fits. |
