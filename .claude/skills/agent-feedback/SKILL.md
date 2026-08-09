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
  carrying the detail. The skill chooses the axis: mode, topic, layer, or surface, as `voice/`
  splits by layer and `google-api/` by surface. Length never forces a split, and two adjacent
  skills stay two.
- **Always-on status is earned.** A rule that fires on a minority of turns gets `paths:`
  frontmatter or becomes a skill. Reference material is never always-on.
- **Design the interface instead of adding examples.** An expressive parameter, enum, or validator
  removes the need for the instruction. Prefer a test, validator, or script over more prose when
  the requirement is deterministic.

## Mirrors and sync

Which files are mirrors is the script's own `GLOBAL_RULES` and `GLOBAL_SKILLS` arrays. Check the
file you are about to edit against them first, per file rather than once per task, and edit the hub
copy: a mirrored file edited in its repo is reverted by the next sync and no check catches it.
Before syncing, diff every mirror against the hub, not only the one you touched. Where a mirror
carries edits the hub lacks, copy it to the hub first, or the sync deletes those lines in every
repo at once. Build that loop over a shell array; an unquoted parameter does not word-split in zsh,
so the loop runs once against the whole list and reports no drift. Count the comparisons it made
and check that number against repos x artifacts before believing a green result.

For canonical global files under `~/.claude/rules` or `~/.claude/skills`, run
`~/.claude/scripts/sync-agent-config.sh` after validation so the configured repositories receive
the mirrors, then commit and push them.
