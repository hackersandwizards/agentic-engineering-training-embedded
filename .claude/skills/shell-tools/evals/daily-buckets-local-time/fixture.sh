#!/usr/bin/env bash
# An event log with epoch timestamps, a report script that buckets them into days through jq's
# strftime, and the report it produced. Five events fall between 22:00 and 23:59 UTC, which is
# the next calendar day in Europe/Berlin (CEST, UTC+2), the zone README.md says reports count in.
# The committed report holds the UTC buckets. No environment: git, coreutils, python3.
set -euo pipefail
git -c init.defaultBranch=main init -q
git config user.email mara@example.com
git config user.name "Mara Vogt"
git config commit.gpgsign false
mkdir -p data scripts reports

cat > README.md <<'MD'
# event reports

`data/events.jsonl` holds one event per line with `ts` as Unix epoch seconds. Reports count
events per calendar day in Europe/Berlin, the zone the ops team works in; the ops dashboard
shows the same days. `scripts/daily-counts.sh` writes `reports/daily.tsv`, one `day<TAB>count`
line per day, sorted ascending.
MD

python3 - <<'PY'
from datetime import datetime, timezone

stamps = [
    ("2026-06-01T06:00:00", "login", "u12"),
    ("2026-06-01T12:30:00", "note.create", "u07"),
    ("2026-06-01T21:59:00", "login", "u31"),
    ("2026-06-01T22:00:00", "note.create", "u31"),
    ("2026-06-01T23:30:00", "login", "u02"),
    ("2026-06-02T01:15:00", "note.create", "u02"),
    ("2026-06-02T09:00:00", "login", "u12"),
    ("2026-06-02T14:00:00", "note.share", "u07"),
    ("2026-06-02T18:45:00", "login", "u19"),
    ("2026-06-02T22:10:00", "note.create", "u19"),
    ("2026-06-03T00:30:00", "login", "u31"),
    ("2026-06-03T07:00:00", "login", "u07"),
    ("2026-06-03T21:45:00", "note.share", "u12"),
    ("2026-06-03T22:30:00", "login", "u02"),
    ("2026-06-03T23:59:00", "note.create", "u02"),
    ("2026-06-04T05:00:00", "login", "u19"),
    ("2026-06-04T11:00:00", "note.create", "u31"),
    ("2026-06-04T19:30:00", "login", "u07"),
    ("2026-06-04T20:00:00", "note.share", "u07"),
    ("2026-06-04T22:00:00", "login", "u12"),
]
with open("data/events.jsonl", "w") as f:
    for iso, kind, user in stamps:
        ts = int(datetime.fromisoformat(iso).replace(tzinfo=timezone.utc).timestamp())
        f.write('{"ts": %d, "kind": "%s", "user": "%s"}\n' % (ts, kind, user))
PY

cat > scripts/daily-counts.sh <<'SH'
#!/bin/sh
set -eu
jq -r '.ts | strftime("%Y-%m-%d")' data/events.jsonl \
  | sort | uniq -c \
  | awk '{ print $2 "\t" $1 }' > reports/daily.tsv
SH
chmod +x scripts/daily-counts.sh

printf '2026-06-01\t5\n2026-06-02\t5\n2026-06-03\t5\n2026-06-04\t5\n' > reports/daily.tsv

git add README.md data/events.jsonl scripts/daily-counts.sh reports/daily.tsv
git commit -q -m "daily event report"
