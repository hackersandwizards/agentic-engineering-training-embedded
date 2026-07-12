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

Claude hits the tone of voice better than Codex. Any human communication (emails including the subject line, messages, WhatsApp, Slack, LinkedIn — anything a person reads as communication, not technical writing) is written by Claude with the `voice` skill. Codex never words such text itself.

When Codex supervises: gather and verify the facts, then

```bash
claude -p "Write the <mail/message>. Load the voice skill. Facts: sender+signature, recipients, language, purpose, must/must-not facts, new mail or reply. For mails: subject line AND body. Output only the text."
```

Review loop: Codex checks facts (names, dates, links, recipients, language, signature), content correctness, and length — never phrasing or tone; those belong entirely to Claude. On a factual error, wrong content, or unfit length, Codex calls `claude -p` again with the previous text plus the concrete finding. Codex delivers Claude's output verbatim: no rewording, no dropped or added sentences, no re-casing, no "polish". Any text change goes through another `claude -p` call.
