---
name: delegation
description: >-
  Which model tier and effort to run Codex at, how Codex hands authored copy to Claude to
  write, and the one thing Claude starts Codex for. Authored copy is Claude's in both
  directions.
---

# Delegation

## Codex model tiers

Default: `gpt-6-astra`, effort `low`, chosen on cost. Plan mode runs `high`. `.codex/config.toml` sets both and
decides the default.

| Pick | For |
|------|-----|
| astra low | everyday coding |
| astra high | planning, hard bugs, architecture, final review |
| luna high | eval runs, where the fixture is fixed and volume sets the cost |

- Astra accepts `low`, `medium`, `high`, `xhigh`, `max`. It has no `none`.
- `codex exec --model` overrides the config per invocation. The email-reply evals run luna.

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

## Claude -> Codex

Claude starts Codex only for a capability Claude does not have, and never to author text. Image
generation is that capability today.

Verify what a run did with `git log`, never from its own summary.
