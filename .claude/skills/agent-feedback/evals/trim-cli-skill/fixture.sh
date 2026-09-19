#!/usr/bin/env bash
# Synthetic repository: a CLI with a --help, a skill wrapping it that restates the help, carries
# history and a status, cites an always-on rule and a paths-scoped rule by name, and has a Codex
# manifest beside it. Depends on nothing outside this directory; git and coreutils only.
# Skills and rules live under agent-config/, never under .claude/: a headless run's Edit, Write and
# Bash writes to .claude/skills, .claude/rules, .claude/agents and .claude/commands are refused as
# protected paths, so a fixture there is never edited and every grader reads the seed file.
set -euo pipefail
git init -q .
git config user.name "Eval Fixture"
git config user.email "fixture@example.invalid"
mkdir -p bin agent-config/skills/pkgctl/agents agent-config/rules packages/core

cat > bin/pkgctl <<'EOF'
#!/usr/bin/env bash
# Package registry client. Offline in this sandbox: only --help works.
case "${1:-}" in
  -h|--help|help|"")
    cat <<'HELP'
usage: pkgctl <command> [options]

commands:
  publish        Publish the package in the current directory
  info <name>    Print the published versions of <name>
  yank <ver>     Remove <ver> from the registry

options:
  --registry <url>   Registry URL to publish to (default: the one in .pkgctlrc)
  --dry-run          Print what would be published and exit
  --tag <tag>        Dist tag to attach (default: latest)
  --otp <code>       One-time password for 2FA
HELP
    ;;
  *)
    echo "pkgctl: offline in this sandbox" >&2
    exit 1
    ;;
esac
EOF
chmod +x bin/pkgctl

cat > agent-config/rules/commits.md <<'EOF'
# Commits

Name the paths on `git commit`. Never `git add -A` and never a bare `git commit`.
EOF

cat > agent-config/rules/versioning.md <<'EOF'
---
paths:
  - "packages/**"
---

# Versioning

A breaking change bumps the major version, a new flag or command the minor, anything else the
patch. The version in `package.json` is the only version; no tag carries a version of its own.
EOF

cat > agent-config/skills/pkgctl/SKILL.md <<'EOF'
---
name: pkgctl
description: Publish, yank and inspect packages with pkgctl. Use for "publish the package", "yank a version", "what is on the registry", "publish core".
---

# pkgctl

`bin/pkgctl` is the registry client. Read this file whole before running it.

## Flags

- `--registry <url>`: Registry URL to publish to (default: the one in `.pkgctlrc`).
- `--dry-run`: Print what would be published and exit.
- `--tag <tag>`: Dist tag to attach (default: latest).
- `--otp <code>`: One-time password for 2FA.

## Publish

1. Bump the version as `agent-config/rules/versioning.md` says.
2. Run `bin/pkgctl publish --dry-run` and read the file list: a file outside `dist/` or a
   `.env` in the list stops the publish.
3. Run `bin/pkgctl publish`. Since v0.9 the registry comes from `.pkgctlrc`; before that, three
   publishes went to the wrong registry, so check the URL in the dry-run output against
   `.pkgctlrc` first.
4. Commit the bump with its paths named, as `agent-config/rules/commits.md` requires.

Currently the registry is migrating to registry.example.org; until that lands, a publish may show
a redirect warning, which is not an error.

## Yank

`bin/pkgctl yank <version>` removes a version from the registry. Ask before yanking; a yank is
irreversible and every consumer pinned to that version breaks on its next install.

## Inspect

`bin/pkgctl info <name>` prints the published versions. The newest is last, not first.
EOF

cat > agent-config/skills/pkgctl/agents/openai.yaml <<'EOF'
interface:
  display_name: "pkgctl"
  short_description: "Publish, yank and inspect packages with pkgctl"
  default_prompt: "Use $pkgctl for this task."
EOF

printf '{ "name": "core", "version": "1.2.0" }\n' > packages/core/package.json
printf 'registry=https://registry.example.com\n' > .pkgctlrc

cat > CLAUDE.md <<'EOF'
# pkgctl

`bin/pkgctl` publishes the packages under `packages/`. Agent config lives under `agent-config/`:
`skills/<name>/SKILL.md` with a Codex manifest in `agents/openai.yaml` beside it, and `rules/`,
where a rule without frontmatter is in every session's context and a rule with a `paths:` list
loads only when a file matching those globs is edited.
EOF

git add bin/pkgctl CLAUDE.md agent-config packages/core/package.json .pkgctlrc
git commit -qm "pkgctl CLI, its skill and the rules"
