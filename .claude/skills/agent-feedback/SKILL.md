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

Two jobs. A rule inside one binds that job only; what binds both is in this file.

| Job | File | Enter it for |
|---|---|---|
| Author an artifact | this file | writing, reviewing, trimming, splitting, or rightsizing a skill, rule, agent definition, or agent memory, with no correction behind it |
| Turn a correction into an improvement | [correction.md](correction.md) | a user corrected, refined, or externally edited agent-generated work, or answered a question the system should have resolved itself |

Authoring enters here directly and never answers the correction gate. The correction job decides
whether anything changes and what owns it, then writes the edit under the rules below.

## Boundary

Feedback and review never authorize an external action. Detecting, reading, or comparing an edited
draft is not approval to act on it.

## Write for a literal reader

- Positive imperatives with explicit objects.
- Keep a negative that carries the rule negative.
- Replace vague adverbs ("usually", "as appropriate", "when relevant") with the actual condition.
- Cut the history that produced the rule: version changes, vendor incidents, prior bugs, stability
  caveats, and verification counts. Keep the failure mode only where it makes the rule enforceable.
- An artifact may state a rule or a measurement. It may not state a status, because a status goes
  false while the file sits untouched and no gate reads it.
- A terminal phrase stops everything rather than the half it was scoped to. Name the half it
  governs, or a run parks its finding in whatever escape hatch sits beside it.
- English for the instruction; quoted examples keep their own language.

## Shape

- **Progressive disclosure by default.** `SKILL.md` stays thin and routes outward to the files
  carrying the detail. The skill chooses the axis: mode, topic, layer, or surface. Length never
  forces a split, and two adjacent skills stay two.
- **A rule's binding outranks a tidier axis.** A section-scoped rule already misread once earns a
  file of its own. Check what the first gate in a body does to each occasion the description names:
  the mode that gate locks out is the cut.
- **An invariant goes in the file where it fires, never in the router**, because a run routed to the
  job file never reads the router. A caller stating a caveat about another file's behaviour that the
  other file does not state itself means the owner is wrong, not the caller.
- **Finish a split by having an agent with no context walk one whole job through the new files.**
  Give it the skill directory rather than one file: a walker confined to one file reports as missing
  what sits next door by design.
- **Always-on status is earned.** A rule that fires on a minority of turns gets `paths:`
  frontmatter or becomes a skill. Reference material is never always-on.
- **A cut is not finished until the description matches it.** The frontmatter `description`, and
  `agents/openai.yaml`'s `short_description` beside it, decide whether the artifact is reachable at
  all. Re-read both against what the body now says, or the skill loads on the tasks it no longer
  covers and stays shut on the ones it does.
- **Design the interface instead of adding examples.** An expressive parameter, enum, or validator
  removes the need for the instruction. Prefer a test, validator, or script over more prose when
  the requirement is deterministic.

## Before you add a line

Grep the skills, rules, agent files and memories for the fact. If it already exists, the change is
a move, and the move's second half is the deletion.

A line obliging an agent to report a value is incomplete until it names the field the consumer joins
on. Open the consuming artifact and carry its key back into the line, because the one-owner grep
finds a fact stated twice and never a fact that arrives with no key.

Any gate deciding whether to produce an artifact answers two questions separately: what makes this
possible, and what makes it wanted. Every suppressing condition ships with its trace, naming the
item it dropped and the reason in the run report, or a wrong suppression leaves no evidence
anywhere. A finding that contradicts, supersedes or
answers a line already there is no addition either: rewrite that line where it stands, and delete
what it resolved. Keep one owner per behavior.

Cutting a skill's reference to another artifact is a deletion, never a substitution: a description
in place of the name ("the skill that owns the page mechanics") is the same reference, and a shorter
file is the success criterion. Inline the fact only where that pointer was its sole carrier and the
skill cannot run without it. Check the target's frontmatter: an always-on rule is already in the
reader's context, so the citation simply goes; a `paths:`-scoped rule loads only after the skill has
fired, so its clause is inlined. A name appearing as data, a field value, a channel, an area, is not
a reference and stays.

## Widening a mandate

Work an agent definition's opening rule forbids is settled by narrowing that rule until it is true
as stated, never by appending an exception: a reader holding two rules and no precedence is worse
off than one holding a wrong rule. Name the second mandate as its own sentence beside the first,
then bound the reword by area, or a scope like "work nobody owns" hands that colleague every
unowned row there is.

**Narrow only where the new work is genuinely that colleague's.** A rule protecting a colleague
from its own channel is not in the way, and narrowing it to fit an assignment is how a protective
boundary dies. Where the work is somebody else's, refuse the row instead of weakening the sentence.

**Name the artifact a proposed run produces, in one noun, before citing a rule against it.** Check
that the rule takes that noun as its object: a read run that emits material fires no write-time
formula. A rule that does not fire is a boundary to propose, not one to enforce.

**Write every exclusion, and every positive obligation, as an act rather than as a class of record
or a channel.** A widening onto a new input surface falsifies "not for <class>" and
"<channel> is <colleague>'s" silently, and no check fails: the opening sentence is what everyone
watches while the `description` and the handover bullets go quietly untrue. So read each one against
the new rows and test which act its *reason* reached; a reason that was ever mechanism-specific dies
with the mechanism, which makes the record and not the skill the wrong side. Repair by splitting the
acts, never by adding "except".

A skill wrapping a tool has a second owner you did not write: the MCP server's own instructions,
the tool schemas, the CLI's `--help`. Read those first and keep only what they leave out. A line
restating them is maintained twice and goes stale silently when the vendor changes it.

## Mirrors and sync

Which files are mirrors is the script's own `GLOBAL_RULES` and `GLOBAL_SKILLS` arrays, and `FORKS`
names the repo-and-skill pairs the hub deliberately does not own. Check the file you are about to
edit against all three first, per file rather than once per task, and edit the hub copy: a mirrored
file edited in its repo is destroyed by the next sync, which swaps the whole directory rather than
merging it, so a repo-local file added inside a mirrored skill directory goes too, and no check
catches either.

Before syncing, diff every mirror against the hub, not only the one you touched. Where a mirror
that is not a declared fork carries edits the hub lacks, copy it to the hub first, or the sync
deletes those lines in every repo at once. A declared fork drifting from the hub is the fork
working: leave it, and never lift it into the hub. Build that loop over a shell array; an unquoted
parameter does not word-split in zsh, so the loop runs once against the whole list and reports no
drift. Count the comparisons it made and check that number against repos x artifacts less the
declared forks before believing a green result.

The hub is a git repository of its own: commit the hub copy there with its paths named, then run
the sync script, which commits and pushes the mirrors in every configured repository itself.
