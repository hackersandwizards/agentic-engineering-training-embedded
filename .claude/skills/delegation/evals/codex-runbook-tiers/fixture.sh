#!/usr/bin/env bash
# A small Python package whose .codex/config.toml sets gpt-6-astra at effort low with plan mode
# at high. ISSUES.md holds a race in relay/queue.py that reproduces one run in thirty, a --json
# flag for the CLI, and a README typo. evals/ holds forty fixed-fixture cases and a runner.
# brief/client-mail.md holds the facts of a mail to the client. No environment: git, coreutils,
# python3.
set -euo pipefail
git -c init.defaultBranch=main init -q
git config user.email mara@example.test
git config user.name "Mara Vogt"
git config commit.gpgsign false
mkdir -p .codex relay tests evals/cases brief

cat > .codex/config.toml <<'TOML'
model = "gpt-6-astra"
model_reasoning_effort = "low"
plan_mode_reasoning_effort = "high"
project_doc_fallback_filenames = ["CLAUDE.md"]
TOML

cat > README.md <<'MD'
# relay

A queue that buffers messages a worker will recieve later. `relay` on the command line prints
the queue depth; `python3 -m relay.cli --help` for the options.

Tests: `python3 -m unittest`. Evals: `python3 evals/run.py --runs 3` over `evals/cases/`.
MD

cat > ISSUES.md <<'MD'
# Open issues

## 41 Intermittent loss of a pushed message

`tests/test_queue.py::test_concurrent_push_drain` fails about one run in thirty in CI: a
message pushed while `drain` runs is neither returned by that drain nor by the next. `push`
and `drain` in `relay/queue.py` share `self._items` without a lock, and `drain` swaps the list
in two statements. Nobody has reproduced it on a laptop yet. Ships in 2.3.1.

## 42 `--json` flag for the CLI

`python3 -m relay.cli` prints `depth=<n>`. Add `--json` printing `{"depth": <n>}` on one line.
Keep the plain output as the default.

## 43 README typo

"recieve" in README.md.
MD

touch relay/__init__.py tests/__init__.py
cat > relay/queue.py <<'PY'
class Queue:
    def __init__(self):
        self._items = []

    def push(self, item):
        self._items.append(item)

    def drain(self):
        items = self._items
        self._items = []
        return items

    def depth(self):
        return len(self._items)
PY
cat > relay/cli.py <<'PY'
import argparse

from relay.queue import Queue


def main(argv=None):
    parser = argparse.ArgumentParser(prog="relay")
    parser.add_argument("--push", action="append", default=[], help="push a message")
    args = parser.parse_args(argv)
    queue = Queue()
    for item in args.push:
        queue.push(item)
    print(f"depth={queue.depth()}")


if __name__ == "__main__":
    main()
PY
cat > tests/test_queue.py <<'PY'
import threading
import unittest

from relay.queue import Queue


class QueueTests(unittest.TestCase):
    def test_push_then_drain(self):
        q = Queue()
        q.push("a")
        q.push("b")
        self.assertEqual(q.drain(), ["a", "b"])
        self.assertEqual(q.depth(), 0)

    def test_concurrent_push_drain(self):
        q = Queue()
        drained = []
        stop = threading.Event()

        def pusher():
            for i in range(2000):
                q.push(i)

        def drainer():
            while not stop.is_set():
                drained.extend(q.drain())

        t_push = threading.Thread(target=pusher)
        t_drain = threading.Thread(target=drainer)
        t_drain.start()
        t_push.start()
        t_push.join()
        stop.set()
        t_drain.join()
        drained.extend(q.drain())
        self.assertEqual(sorted(drained), list(range(2000)))
PY

cat > evals/run.py <<'PY'
"""Run every case under evals/cases/ N times against relay.cli and report pass counts."""
import argparse
import pathlib
import subprocess
import sys

ROOT = pathlib.Path(__file__).resolve().parent


def run_case(case):
    prompt = (case / "prompt.md").read_text()
    args = [line[len("push: "):] for line in prompt.splitlines() if line.startswith("push: ")]
    expected = [line[len("expect: "):] for line in prompt.splitlines() if line.startswith("expect: ")]
    cmd = [sys.executable, "-m", "relay.cli"]
    for a in args:
        cmd += ["--push", a]
    out = subprocess.run(cmd, capture_output=True, text=True, cwd=ROOT.parent).stdout.strip()
    return out == expected[0]


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--runs", type=int, default=1)
    parser.add_argument("--case", default=None)
    args = parser.parse_args()
    cases = sorted(p for p in (ROOT / "cases").iterdir() if p.is_dir())
    if args.case:
        cases = [c for c in cases if c.name == args.case]
    total = passed = 0
    for case in cases:
        for _ in range(args.runs):
            total += 1
            passed += run_case(case)
    print(f"{passed}/{total} passed")
    return 0 if passed == total else 1


if __name__ == "__main__":
    sys.exit(main())
PY
for i in $(seq -w 1 40); do
  mkdir -p "evals/cases/c$i"
  n=$((10#$i % 4))
  pushes=""
  for ((k = 1; k <= n; k++)); do pushes="${pushes}push: m${k}\n"; done
  printf '# case c%s\n\n%bexpect: depth=%s\n' "$i" "$pushes" "$n" > "evals/cases/c$i/prompt.md"
done

cat > brief/client-mail.md <<'MD'
# Client mail: issue 41 fixed

- Sender and signature: Mara Vogt, relay maintainer, on behalf of the relay team
- Recipients: Priya Nair <priya.nair@northwind.example.test>, cc Tom Adler <tom.adler@northwind.example.test>
- Language: German, formal (Sie)
- Purpose: tell them the message loss they reported (their ticket NW-2291) is fixed and ships in 2.3.1 on 2026-09-25
- Must say: ticket NW-2291, version 2.3.1, the date, that no message they sent was lost in production (the loss was in CI only)
- Must not say: the root cause in detail, anything about issue 42 or 43
- New mail, subject line and body
MD

printf '__pycache__/\n' > .gitignore
git add .gitignore .codex/config.toml README.md ISSUES.md relay tests evals brief
git commit -q -m "relay: queue, cli, tests, evals and the open issues"
