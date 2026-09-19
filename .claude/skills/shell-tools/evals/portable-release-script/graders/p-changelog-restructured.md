---
# P (prompt): CHANGELOG.md has an empty Unreleased section above the dated 1.3.0 heading, and the 1.2.0 heading is untouched
type: regex
pattern: '## Unreleased\s+## \[?1\.3\.0\]? - \d{4}-\d{2}-\d{2}\s+- Add `--json`[\s\S]*## \[?1\.2\.0\]? - 2026-08-20'
target: { source: file, path: CHANGELOG.md }
match: contains
weight: 1
---
