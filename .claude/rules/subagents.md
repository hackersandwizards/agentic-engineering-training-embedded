# Subagents

- Running unattended, say so in every subagent prompt you write. A fresh delegate inherits none of
  your context and will otherwise stop to ask.
- Where one colleague owns an outbound channel and another decides the case, the deciding colleague
  writes the records and hands the drafter the recipient, the thread, the facts, and the skill
  section that constrains the draft. Any other unattended run drafts its own outbound mail.
- A brief naming a channel lets the delegate draft there and never forbids it: a draft is not a
  send.
- Delegating never widens scope. Name the work in the prompt, and have anything the delegate judges
  to need more come back as a decision for the principal. The prompt cannot enforce this: a
  delegate's tools come from its own definition, never from the caller's.
- A delegate reviewing credential handling reasons from the source, and the prompt says so: no
  command that reads a keychain, a credential helper or a secret store. A printed value stays in a
  transcript, and only a person can rotate it.
- Delegates in one session share its scratchpad. Prefix every scratch file with its run, and fetch
  into a directory named for the run, since a resume guard adopts files another run left.
- Check that SendMessage is available before fanning out: a fan-out you cannot prod runs serially
  in your own context. Prod a quiet agent with SendMessage for its findings and do other work
  meanwhile. Never spawn a replacement for a silent agent, and never end a turn while a phase is
  still owed its report. Where an agent is gone for good, do that phase yourself.
- A delegate's own delegates report to the top-level session, never to the delegate that spawned
  them. The top session relays each such report to its spawner with SendMessage when it arrives.
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
- Add an MCP server, permission or hook at project scope (`.mcp.json` or `.claude/settings.json` in
  the folder it serves), never `settings.local.json` or user scope, unless the person names that
  scope.
- Only work that must notice an absence earns a schedule. Deterministic work becomes a gate, and
  event-driven work becomes an agent the event calls. A run a person triggers at your request is
  your run, so say what it will do in the world when you ask for the trigger.
- A scheduled task carries only what is true because it runs on a schedule: the cadence, the
  colleague it delegates to, the standing approval and its limit, and the ledger that dedupes
  across runs. A standing approval names the acts that leave the company and their limits, and
  covers record writes as those the skill names: a skill change that needs a task edit means the
  approval was written too fine. The procedure sits in a skill the task loads, counts included, so
  every run of a task is identical: a count that seems to differ by weekday becomes one number in
  the skill. Every run ends its report with its outcome, done, deferred or blocked, and the reason
  for anything but done. A task's identifier is immutable, so a rename is a delete plus a create,
  and the new registration inherits neither its last-run time nor its tool grants.
  Its model and permission mode live on that registration in the app's `scheduled-tasks.json`,
  its tool grants in the app, never in the task's `SKILL.md`. Change them in the app's edit form:
  the app rewrites that file from its own store and has dropped a permission mode edited there.
- Name a skill for its function and a scheduled task for its job, with the cadence as the last
  segment.
