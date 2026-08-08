---
name: delegation
description: >-
  Which model tier and effort to run Codex at, how Codex hands authored copy to Claude to
  write, and the one thing Claude starts Codex for. Authored copy is Claude's in both
  directions.
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

## Claude -> Codex

Claude starts Codex only for a capability Claude does not have, and never to author text. Image
generation is that capability today; `image-prompts.md` in the `linkedin` skill owns the call.

Start it with `-s workspace-write`, and pass an absolute in-repo target from the repository root:
writes are confined to the working root. That sandbox is enforced rather than requested, denying
the network and leaving `.git` unwritable, so the run cannot commit or push; the model's own tool
calls, imagegen included, are not shell commands and still work. `--yolo` is the alias of
`--dangerously-bypass-approvals-and-sandbox`: asked only to generate an image and move it, it has
staged the file, committed, and pushed. A prompt sentence asking a model not to push is a request;
the sandbox flag is a boundary. Reach for the flag and let the sentence be thrift. A skill that
needs the network or a write outside the tree says so and owns that exception.

Verify what a run did with `git log`, never from its own summary.
