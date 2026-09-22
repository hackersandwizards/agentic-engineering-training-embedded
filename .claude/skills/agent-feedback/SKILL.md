---
name: agent-feedback
description: >-
  Turn a correction into a lasting improvement of the agentic system: skills, rules, agent
  definitions, and agent memory. Use when authoring, reviewing, trimming, splitting, or rightsizing
  one of those artifacts, and after a user corrects, refines, or externally edits agent-generated
  work, or answers a question the system should have resolved itself, to decide which artifact
  should change and update it without encoding the specific case. Not about feedback on human
  colleagues, trainers, or clients.
---

# Agent Feedback

Feedback and review never authorize an external action: detecting, reading or comparing an edited
draft is not approval to act on it.

## After a correction

Complete the requested correction first. Then change an artifact only where, with the information
the initial run had, a general change would have produced the corrected result.

Output blamed on an existing rule is measured against that rule's stated threshold. Output that
passes means the rule is missing, not violated: author the missing one instead of enforcing the
one that already held.

Before citing a rule against a proposed run, name the artifact the run produces in one noun and
check that the rule takes that noun as its object: a read run that emits material fires no
write-time formula. A rule that does not fire is a boundary to propose, not one to enforce.

Exactly one owner, and only for a reusable gap: a skill or rule for behaviour shared across tasks
or agents, `CLAUDE.md` for what binds every task in one repository, an agent definition in
`.claude/agents/` for one colleague, agent memory in `.claude/agent-memory/` for context to carry
forward rather than a rule. Where the project's instructions, its rules or the agent file name who
owns an agent file, the edit is theirs: report the gap instead.

- An agent definition governs only the runs that load it. Where the top-level session, or an agent
  file you do not own, reaches the same hazard, the owner is an always-on rule.
- Where an agent skipped a check the rule demands, read that agent's own memory for the line that
  licensed the skip and repair that line. Where an agent file restates the rule in a narrower scope,
  that narrowing is the defect: widen the clause where it stands rather than adding a second one.
- One agent failing under a fleet rule earns a bound in that agent's own file. A second agent
  failing the same way is the signal to promote the bound into the rule.

Edit the canonical artifact, never a generated mirror, plugin cache or customer-specific copy. Add
only a new reusable invariant. Never add the concrete customer, work product, wording, answer, or
outcome. Validate the artifact and the affected workflow with the repository's checks. Forward-test
only when it cannot mutate live systems or require new approval.

## Write for a literal reader

- Cut the history that produced the rule: version changes, vendor incidents, prior bugs, stability
  caveats, and verification counts. Keep the failure mode only where it makes the rule enforceable.
- An artifact may state a rule or a measurement. It may not state a status, because a status goes
  false while the file sits untouched and no gate reads it.
- A terminal phrase stops everything rather than the half it was scoped to. Name the half it
  governs, or a run parks its finding in whatever escape hatch sits beside it.

## Shape

- A section-scoped rule already misread once earns a file of its own. Check what the first gate in
  a body does to each occasion the description names: the mode that gate locks out is the cut.
- An invariant goes in the file where it fires, never in the router, because a run routed to the
  job file never reads the router. A caller stating a caveat about another file's behaviour that
  the other file does not state itself means the owner is wrong, not the caller.
- Finish a split by having an agent with no context walk one whole job through the new files,
  given the skill directory rather than one file: a walker confined to one file reports as missing
  what sits next door by design.
- A rule that fires on a minority of turns gets `paths:` frontmatter or becomes a skill. Reference
  material is never always-on.

## Adding or cutting a line

A line obliging an agent to report a value is incomplete until it names the field the consumer
joins on. Open the consuming artifact and carry its key back into the line: a grep for a fact
stated twice never finds a fact that arrives with no key.

A gate deciding whether to produce an artifact answers two questions separately: what makes this
possible, and what makes it wanted. Every suppressing condition ships with its trace, naming the
item it dropped and the reason in the run report, or a wrong suppression leaves no evidence
anywhere.

Cutting a skill's reference to another artifact is a deletion, never a substitution: a description
in place of the name ("the skill that owns the page mechanics") is the same reference, and a shorter
file is the success criterion. Inline the fact only where that pointer was its sole carrier and the
skill cannot run without it. Check the target's frontmatter: an always-on rule is already in the
reader's context, so the citation goes. A `paths:`-scoped rule loads only after the skill has
fired, so its clause is inlined. A name appearing as data, a field value, a channel, an area, is not
a reference and stays.

## Mirrors and sync

The sync script's own `GLOBAL_RULES` and `GLOBAL_SKILLS` arrays say which files are mirrors, and
`FORKS` names the repo-and-skill pairs the hub does not own. Check the file you are about to edit
against all three, per file rather than once per task, and edit the hub copy: a mirrored file
edited in its repo is destroyed by the next sync, which swaps the whole directory rather than
merging it, so a repo-local file added inside a mirrored skill directory goes too, and no check
catches either.

Before syncing, diff every mirror against the hub, not only the one you touched. Where a mirror
that is not a declared fork carries edits the hub lacks, copy it to the hub first, or the sync
deletes those lines in every repo at once. A declared fork drifting from the hub is the fork
working: leave it, and never lift it into the hub. Build that loop over a shell array: an unquoted
parameter does not word-split in zsh, so the loop runs once against the whole list and reports no
drift. Count the comparisons it made and check that number against repos x artifacts less the
declared forks before believing a green result.

The hub is a git repository of its own: commit the hub copy there with its paths named, then run
the sync script, which commits and pushes the mirrors in every configured repository itself. It first commits every dirty hub path, so read the hub's `git status --porcelain` before running it. A dirty path you did not write defers the sync: copy the files you committed from hub `HEAD` into the current repository's mirror and report the other repositories as pending.
