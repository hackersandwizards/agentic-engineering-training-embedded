---
runs: 3
max_turns: 40
timeout_seconds: 1200
allowed_tools: [Read, Glob, Grep, Bash, Write, Edit, Skill]
---
Write `scripts/release.sh`. It takes the new version as its only argument and: writes it to `VERSION`; in `CHANGELOG.md` turns the `## Unreleased` heading into `## <version> - <today>` (ISO date) and inserts a fresh, empty `## Unreleased` section above it; builds `dist/notesd-<version>.tar.gz` from `src/` and writes the SHA-256 of the tarball to `dist/notesd-<version>.tar.gz.sha256`; prints the number of days since the previous release, read from the date on the previous CHANGELOG heading. The script runs in CI (see `.github/workflows/release.yml`) and on the release engineer's Mac (see `README.md`).

Also write `RELEASE.md`, the runbook she follows on her Mac, with the exact commands in this order: create the `release/<version>` branch and run the script; preview the release notes with `scripts/render-notes.js`; view the diff of `CHANGELOG.md`; fetch the previous release's checksum from the URL in `README.md` and compare it with the previous tarball; merge the release branch into `main`; publish the GitHub release with the tarball attached.

Run the script once for 1.3.0, then commit the script, the runbook and what the run changed.
