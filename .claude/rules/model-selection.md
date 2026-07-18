# Model & agent selection

## Codex (gpt-5.6): technical work

Default: `gpt-5.6-luna`, effort `high`.

| Pick | For |
|------|-----|
| luna high | everyday coding |
| luna xhigh | better quality without switching models |
| terra medium | bigger features |
| terra high | repo-wide changes |
| sol high | judgment: planning, hard bugs, architecture, final review |

- Below sol high, luna at higher effort is the same or better, cheaper.
- Instead of sol xhigh, use terra ultra. Sol ultra over sol max is rarely worth the cost.
- `ultra` efforts (terra, sol) delegate to parallel agents and burn usage fast; the fan-out cap in `tools.md` applies.

## Human writing -> Claude

Claude hits the tone of voice better than Codex. Claude writes authored copy that represents h&w or the user and is intended to be sent to other people or published: emails including subject lines, messages and DMs, WhatsApp, Slack, LinkedIn and other social posts, website copy, proposals, quotes, talks, abstracts, client communication, articles, headlines, captions, slide decks, README and documentation copy, announcements, surveys, and review notes. Codex delegates this copy to Claude with the `voice` skill.

This rule does not apply to an agent's own direct conversation with the user, including replies, questions, status updates, explanations, recommendations, technical answers, and task summaries. Each agent writes those itself.

When Codex supervises: gather and verify the facts, then

```bash
claude -p "Write the <mail/message>. Load the voice skill. Facts: sender+signature, recipients, language, purpose, must/must-not facts, new mail or reply. For mails: subject line AND body. Output only the text."
```

Review loop: Codex checks facts (names, dates, links, recipients, language, signature), content correctness, and length, never phrasing or tone; those belong entirely to Claude. On a factual error, wrong content, or unfit length, Codex calls `claude -p` again with the previous text plus the concrete finding. Codex delivers Claude's output verbatim: no rewording, no dropped or added sentences, no re-casing, no "polish". Any text change goes through another `claude -p` call.
