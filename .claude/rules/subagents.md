# Subagents

- Running unattended, say so in every subagent prompt you write. A fresh delegate inherits none of
  your context and will otherwise stop to ask.
- Where one colleague owns an outbound channel and another decides the case, the deciding colleague
  writes the records and hands the drafter the recipient, the thread, the facts, and the skill
  section that constrains the draft. Any other unattended run drafts its own outbound mail.
- Delegating never widens scope. Name the work in the prompt, and have anything the delegate judges
  to need more come back as a decision for the principal. The prompt cannot enforce this: a
  delegate's tools come from its own definition, never from the caller's.
- A delegate reviewing credential handling reasons from the source, and the prompt says so: no
  command that reads a keychain, a credential helper or a secret store. A printed value stays in a
  transcript, and only a person can rotate it.
- Check that SendMessage is available before fanning out: a fan-out you cannot prod runs serially
  in your own context. Prod a quiet agent with SendMessage for its findings and do other work
  meanwhile. Never spawn a replacement for a silent agent, and never end a turn while a phase is
  still owed its report. Where an agent is gone for good, do that phase yourself.
- Wait for a background command with `Monitor` and an `until` loop, or start it with
  `run_in_background` and wait on its exit. A foreground `sleep` chained to a check is blocked.
- Stop a finished delegate's task before you stop the process it left running. Stopping the process
  first wakes the delegate to re-report its whole context, which cost two 650,000-token re-sends in
  one evening. Leave idle entries of finished delegates alone. Read the scratch folder named in a
  process's command line before stopping it: it may be a live delegate's run.
- A stall, a timeout or a resumed transcript means a delegate's report may be incomplete. Read its
  commits and working tree over the window, reconcile every hunk against what it said it did, count
  the files it opened against the files you assigned, and hand any contradiction back.
- A delegate reports a defect inside the window you set. Sweep the repository for the class before
  relaying it as fixed.
- Verify a claim before sending a running delegate a retraction: a late retraction lands as a
  second instruction on finished work.
- Before putting a question to a principal, re-read what you told the delegate. Decide it in the
  instruction, or hold the work and ask, never both.
- Before building or changing Claude Code artifacts (skills, rules, subagents, hooks, settings,
  MCP), consult the `claude-code-guide` agent or the official docs. A rule asserting how the system
  behaves is checked against the system before it is written and before it is leaned on.
- Only work that must notice an absence earns a schedule. Deterministic work becomes a gate, and
  event-driven work becomes an agent the event calls. A run a person triggers at your request is
  your run, so say what it will do in the world when you ask for the trigger.
- A scheduled task carries only what is true because it runs on a schedule: the cadence, the
  colleague it delegates to, the standing approval and its limit, and the ledger that dedupes
  across runs. The procedure sits in a skill the task loads. A task's identifier is immutable, so a
  rename is a delete plus a create, and the new registration inherits neither its last-run time nor
  its tool grants.
- Name a skill for its function and a scheduled task for its job, with the cadence as the last
  segment.
