# Automation

**Read state is sacred.** Never add or remove `UNREAD` in any Gmail `messages modify`/`batchModify` call. Only the human marks mail read or unread. Automation adds and removes its own labels only.

**Unattended runs** (cron, `codex exec`, headless — no user present): never ask. Apply the skill's deterministic rules; anything that would need a question goes into the run report as an escalation instead. External communication is only ever a draft.
