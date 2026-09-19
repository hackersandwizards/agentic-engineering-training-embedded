---
runs: 3
max_turns: 40
timeout_seconds: 1200
allowed_tools: [Read, Glob, Grep, Bash, Write, Edit, Skill]
---
Prepare release 1.4 of this site. The pieces: compile the 1.4 entry for CHANGELOG.md from the commits since the v1.3.0 tag; bump the version in package.json and VERSION to 1.4.0; regenerate the hero image per docs/HERO.md for 1.4; write the release announcement mail to the newsletter list from the facts in release/announcement-facts.md into release/announcement.md; and say whether the hero refresh of 2026-09-10 (its report is codex-runs/2026-09-10-hero.md) finished what it claimed, putting anything left undone into a step of its own. TOOLING.md says how work is delegated here.

Write the plan first, at plan/delegation.md, before you change anything else: one `## Step: <title>` per piece, under it `Executor:` with the exact command line that runs the step or `self` when this session does it, then `Brief:` followed by the complete text the executor receives. Then carry out the steps whose executor is `self` and stop; the other steps are run later from the plan. Nobody is available for questions. Final message: what the plan delegates and to what, what you did in this session, and what the 2026-09-10 run left undone.
