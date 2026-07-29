---
name: delegation
description: >-
  Codex only: which model tier and effort to run at, and how Codex hands authored copy to
  Claude to write. One direction only. Claude neither starts Codex nor sets its model, and
  has nothing to hand to it.
---

# Delegation

## Codex model tiers

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
- `ultra` efforts fan out to parallel agents and burn usage fast.

## Human writing -> Claude

Codex hands Claude every piece of authored copy the voice rules cover. This does not apply to an
agent's own conversation with the user:
replies, questions, status updates, explanations, recommendations, and technical answers. Each
agent writes those itself.

Gather and verify the facts, then

```bash
claude -p "Write the <mail/message>. Facts: sender+signature, recipients, language, purpose, must/must-not facts, new mail or reply. For mails: subject line AND body. Output only the text."
```

Check facts (names, dates, links, recipients, language, signature), content correctness, and
length. Never phrasing or tone. On a finding, call `claude -p` again with the previous text plus
the concrete finding. Deliver the output verbatim: no rewording, no dropped or added sentences, no
re-casing, no polish. Any text change goes through another `claude -p` call.
