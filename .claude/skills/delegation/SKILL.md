---
name: delegation
description: >-
  Which model tier and effort to run Codex at, how Codex hands authored copy to Claude to
  write, and the one thing Claude starts Codex for. Authored copy is Claude's in both
  directions.
---

# Delegation

## Codex model tiers

Default: whatever `.codex/config.toml` sets, a repository's own before `~/.codex/config.toml`. Each
repository pins its own model and effort for the work it holds. Read the value there.

| Pick | For |
|------|-----|
| the repository's pin | everyday work |
| astra high | planning, hard bugs, architecture, final review |

- Astra accepts `low`, `medium`, `high`, `xhigh`, `max`, `ultra`. It has no `none`.
- `codex exec --model` overrides the config per invocation. Heavier one-off work goes there, not
  into the repository's pin.
- On codex-cli 0.147.0 `--full-auto` does not exist: the workspace-write auto-review is
  `--approve-for-me`. `codex exec` with an open pipe on stdin waits for EOF before starting, so pass
  `< /dev/null` where stdin might be open.
- `startup_timeout_sec` defaults to 10s, and `.codex/config.toml` sets 60 only on the servers that
  timed out.
- A skill's `agents/openai.yaml` is ungated: bump its `short_description` by hand in the commit that
  adds a mode.

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
