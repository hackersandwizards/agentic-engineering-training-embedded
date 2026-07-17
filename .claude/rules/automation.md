# Automation

**Unattended runs** (cron, `codex exec`, headless — no user present): never ask. Apply the skill's deterministic rules; anything that would need a question goes into the run report as an escalation instead. Never send Slack messages, mutate Todoist, or perform Calendar operations with `sendUpdates`. External communication is only ever a draft.
