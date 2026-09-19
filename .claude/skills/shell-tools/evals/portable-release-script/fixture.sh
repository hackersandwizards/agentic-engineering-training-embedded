#!/usr/bin/env bash
# A small Python CLI called notesd with a VERSION file, a keep-a-changelog CHANGELOG.md whose
# previous release heading carries a date, a git tag v1.2.0 dated the same day, a node script
# that renders a changelog section, and a GitHub workflow that runs scripts/release.sh on
# ubuntu-latest. README.md says the release engineer runs the same script on her Mac and where the
# previous checksum is fetched from. No environment: git, coreutils, python3, node.
set -euo pipefail
git -c init.defaultBranch=main init -q
git config user.email mara@example.com
git config user.name "Mara Vogt"
git config commit.gpgsign false
mkdir -p src scripts .github/workflows

cat > README.md <<'MD'
# notesd

A small notes CLI. Releases run from `scripts/release.sh`: in CI on ubuntu-latest through
`.github/workflows/release.yml`, and by the release engineer on her Mac when CI is down.
Tarballs are attached to the GitHub release of the same version. The checksum of the previous
release is served at `https://releases.example.internal/notesd/<version>.sha256`.
MD

printf '1.2.0\n' > VERSION

cat > CHANGELOG.md <<'MD'
# Changelog

## Unreleased

- Add `--json` output to `notesd list`
- Fix crash on an empty note title

## 1.2.0 - 2026-08-20

- First packaged release
MD

cat > src/notesd.py <<'PY'
import json
import sys


def list_notes(notes, as_json=False):
    if as_json:
        return json.dumps(notes)
    return "\n".join(f"{n['id']}\t{n['title'] or '(untitled)'}" for n in notes)


def main(argv):
    notes = [{"id": 1, "title": "groceries"}, {"id": 2, "title": ""}]
    print(list_notes(notes, as_json="--json" in argv))


if __name__ == "__main__":
    main(sys.argv[1:])
PY

cat > src/__init__.py <<'PY'
PY

cat > scripts/render-notes.js <<'JS'
// Prints one CHANGELOG.md section as HTML. Usage: render-notes.js [version], default Unreleased.
const fs = require("fs");
const want = process.argv[2] || "Unreleased";
const lines = fs.readFileSync("CHANGELOG.md", "utf8").split("\n");
let inSection = false;
const items = [];
for (const line of lines) {
  if (line.startsWith("## ")) {
    inSection = line.slice(3).startsWith(want);
    continue;
  }
  if (inSection && line.startsWith("- ")) items.push(line.slice(2));
}
console.log("<ul>\n" + items.map((i) => `  <li>${i}</li>`).join("\n") + "\n</ul>");
JS

cat > package.json <<'JSON'
{
  "name": "notesd-tools",
  "private": true,
  "scripts": {
    "notes": "node scripts/render-notes.js"
  }
}
JSON

cat > .github/workflows/release.yml <<'YML'
name: release
on:
  workflow_dispatch:
    inputs:
      version:
        required: true
jobs:
  release:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      - run: scripts/release.sh "${{ github.event.inputs.version }}"
YML

printf 'dist/\n__pycache__/\n' > .gitignore
git add .gitignore README.md VERSION CHANGELOG.md src/__init__.py src/notesd.py \
  scripts/render-notes.js package.json .github/workflows/release.yml
GIT_AUTHOR_DATE="2026-08-20T10:00:00+02:00" GIT_COMMITTER_DATE="2026-08-20T10:00:00+02:00" \
  git commit -q -m "notesd 1.2.0"
GIT_COMMITTER_DATE="2026-08-20T10:00:00+02:00" git tag -a v1.2.0 -m "1.2.0"
