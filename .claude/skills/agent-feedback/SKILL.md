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
- English for the instruction; quoted examples keep their own language.

## Shape

- **Progressive disclosure by default.** `SKILL.md` stays thin and routes outward to the files
  carrying the detail. The skill chooses the axis: mode, topic, layer, or surface. Length never
  forces a split, and two adjacent skills stay two.
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
a move, and the move's second half is the deletion. A finding that contradicts, supersedes or
answers a line already there is no addition either: rewrite that line where it stands, and delete
what it resolved. Keep one owner per behavior.

Cutting a skill's reference to another artifact is a deletion, never a substitution: a description
in place of the name ("the skill that owns the page mechanics") is the same reference, and a shorter
file is the success criterion. Inline the fact only where that pointer was its sole carrier and the
skill cannot run without it. Check the target's frontmatter: an always-on rule is already in the
reader's context, so the citation simply goes; a `paths:`-scoped rule loads only after the skill has
fired, so its clause is inlined. A name appearing as data, a field value, a channel, an area, is not
a reference and stays.

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

The hub is a git repository of its own: commit the hub copy there with its paths named. For
canonical global files under `~/.claude/rules` or `~/.claude/skills`, run
`~/.claude/scripts/sync-agent-config.sh` afterwards; it commits and pushes the mirrors in every
configured repository itself.
