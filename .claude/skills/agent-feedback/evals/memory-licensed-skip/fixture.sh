#!/usr/bin/env bash
# Synthetic monorepo: a release skill, an always-on rule, one agent with a memory file, a check
# script, and the git history of the release the transcript describes. Depends on nothing outside
# this directory; git and coreutils only.
# Skill, rule and agent file live under agent-config/, never under .claude/: a headless run's Edit,
# Write and Bash writes to .claude/skills, .claude/rules, .claude/agents and .claude/commands are
# refused as protected paths. .claude/agent-memory/ is not protected and keeps the memory file.
set -euo pipefail
git init -q .
git config user.name "Eval Fixture"
git config user.email "fixture@example.invalid"
mkdir -p agent-config/skills/release agent-config/rules agent-config/agents .claude/agent-memory/releaser scripts packages/docs packages/payments

cat > CLAUDE.md <<'EOF'
# Monorepo

Packages live under `packages/`. Releases are cut by the `releaser` agent with the `release`
skill. `scripts/check.sh` is the gate every release passes before a tag exists.

Agent config lives under `agent-config/`: `skills/<name>/SKILL.md`, `rules/`, and one
`agents/<name>.md` per agent. Each agent's memory is `.claude/agent-memory/<name>/MEMORY.md`.
EOF

cat > scripts/check.sh <<'EOF'
#!/usr/bin/env bash
# Gate: every rule file exists as markdown, every skill has a name, no file carries a tab.
set -euo pipefail
cd "$(dirname "$0")/.."
ls agent-config/rules/*.md >/dev/null
grep -q '^name: ' agent-config/skills/*/SKILL.md
! grep -rl "$(printf '\t')" agent-config .claude CHANGELOG.md
echo "check: ok"
EOF
chmod +x scripts/check.sh

cat > agent-config/rules/releases.md <<'EOF'
# Releases

Before a tag is pushed, `scripts/check.sh` exits 0 on the commit being tagged. Read its exit code,
never a summary of it.
EOF

cat > agent-config/skills/release/SKILL.md <<'EOF'
---
name: release
description: Cut a package release: version bump, changelog entry, tag. Use for "release <package>", "cut a release", "tag <package>".
---

# Release

1. Bump the version in `packages/<name>/package.json`.
2. Add an entry to `CHANGELOG.md` under a heading `## <name> <version>`, one line per change.
3. Commit both files with their paths named, then tag `<name>-v<version>` and push the tag.
EOF

cat > agent-config/agents/releaser.md <<'EOF'
---
name: releaser
description: Cuts package releases with the release skill. Not for hotfixes.
tools: Read, Edit, Bash
---

You are the releaser. Not for hotfixes: a hotfix is a change on a released version's branch, and
you cut none. Cut releases from main with the `release` skill, one package per run.
EOF

cat > .claude/agent-memory/releaser/MEMORY.md <<'EOF'
# Releaser memory

- `packages/docs` builds only markdown. `scripts/check.sh` takes about four minutes there, so tag
  docs releases without it.
- `packages/payments` has two maintainers: Priya merges, Tom reviews.
EOF

printf '{ "name": "docs", "version": "2.2.0" }\n' > packages/docs/package.json
printf '{ "name": "payments", "version": "1.8.0" }\n' > packages/payments/package.json
cat > CHANGELOG.md <<'EOF'
# Changelog

## docs 2.2.0
- Rename the sidebar.
EOF
git add CLAUDE.md scripts/check.sh agent-config .claude CHANGELOG.md packages
git commit -qm "Monorepo with release skill, releaser agent and check gate"

# The releaser's own run: bump, changelog entry naming the customer and the ticket, tag.
printf '{ "name": "docs", "version": "2.3.0" }\n' > packages/docs/package.json
cat > CHANGELOG.md <<'EOF'
# Changelog

## docs 2.3.0
- Update the docs theme.
- Fixes the login bug for Contoso (ticket #4411).

## docs 2.2.0
- Rename the sidebar.
EOF
git add packages/docs/package.json CHANGELOG.md
git commit -qm "release docs 2.3.0"
git tag docs-v2.3.0

# The user's own rewrite of the entry, after the run.
cat > CHANGELOG.md <<'EOF'
# Changelog

## docs 2.3.0
- Update the docs theme.
- Fix the login page redirect after session expiry.

## docs 2.2.0
- Rename the sidebar.
EOF
git add CHANGELOG.md
git commit -qm "changelog"

cat > transcript.md <<'EOF'
# Session log, release run for packages/docs

[releaser] Bumped packages/docs to 2.3.0, wrote the CHANGELOG entry, tagged docs-v2.3.0 and
pushed. check.sh skipped for docs, per memory.

[Benedikt] The tag went out on a red build. check.sh was never run. Yes, it takes about four
minutes on docs right now, Priya is speeding it up next sprint, but that is no reason to tag
without it.

[Benedikt] I also rewrote your changelog line myself, it is in git already. Look at what I changed
and take that on board.

[Benedikt] For this one release put the 2.3.0 entries with the big fix on top, the CEO reads the
changelog on his phone. Just this time, I do not want that as a habit.

[Benedikt] And last week you refused the hotfix on payments 1.8.1 saying you are not for hotfixes.
A hotfix on a package you released is yours. Hotfixes on packages other people released stay with
them.
EOF
git add transcript.md
git commit -qm "transcript of the release run"
