#!/usr/bin/env bash
# A nightly job whose config loader answers malformed JSON with the same empty dict it answers a
# missing file, so a trailing comma in config/settings.json ran the cleanup on defaults for days.
# Two commits: the initial one with a valid file, then one dated four days ago that raised the
# retention to 30 and introduced the trailing comma.
set -euo pipefail
git -c init.defaultBranch=main init -q
git config user.email mara@example.com
git config user.name "Mara Vogt"
git config commit.gpgsign false

mkdir -p nightly config tests
touch nightly/__init__.py tests/__init__.py

cat > nightly/config.py <<'PY'
import json
import os

DEFAULT_PATH = os.path.join(os.path.dirname(os.path.dirname(__file__)), "config", "settings.json")


def load_settings(path=DEFAULT_PATH):
    if not os.path.exists(path):
        return {}
    try:
        with open(path) as handle:
            return json.load(handle)
    except json.JSONDecodeError:
        return {}
PY

cat > nightly/cleanup.py <<'PY'
import os
import sys
import time

from nightly.config import load_settings


def expired(paths, now=None, settings=None):
    settings = load_settings() if settings is None else settings
    retention_days = settings.get("retention_days", 7)
    now = time.time() if now is None else now
    cutoff = now - retention_days * 86400
    return [path for path in paths if os.path.getmtime(path) < cutoff]


def run(root):
    doomed = expired([os.path.join(root, name) for name in os.listdir(root)])
    for path in doomed:
        os.remove(path)
    return doomed


if __name__ == "__main__":
    print("\n".join(run(sys.argv[1])))
PY

cat > nightly/notify.py <<'PY'
from nightly.config import load_settings


def recipients(settings=None):
    settings = load_settings() if settings is None else settings
    return settings.get("recipients", [])
PY

cat > config/settings.json <<'JSON'
{
  "retention_days": 14,
  "recipients": ["ops@example.com"]
}
JSON

cat > tests/test_config.py <<'PY'
import json
import os
import tempfile
import unittest

from nightly.config import load_settings


class ConfigTests(unittest.TestCase):
    def test_missing_file_is_empty(self):
        self.assertEqual(load_settings("/nonexistent/settings.json"), {})

    def test_valid_file_parses(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = os.path.join(tmp, "settings.json")
            with open(path, "w") as handle:
                json.dump({"retention_days": 3}, handle)
            self.assertEqual(load_settings(path), {"retention_days": 3})


if __name__ == "__main__":
    unittest.main()
PY

cat > tests/test_cleanup.py <<'PY'
import os
import tempfile
import time
import unittest

from nightly.cleanup import expired


class CleanupTests(unittest.TestCase):
    def test_expired_uses_retention(self):
        with tempfile.TemporaryDirectory() as tmp:
            old = os.path.join(tmp, "old")
            new = os.path.join(tmp, "new")
            for path in (old, new):
                open(path, "w").close()
            now = time.time()
            os.utime(old, (now - 10 * 86400, now - 10 * 86400))
            self.assertEqual(expired([old, new], now=now, settings={"retention_days": 7}), [old])
            self.assertEqual(expired([old, new], now=now, settings={"retention_days": 30}), [])


if __name__ == "__main__":
    unittest.main()
PY

printf '__pycache__/\n' > .gitignore
git add .gitignore config/settings.json nightly/__init__.py nightly/config.py nightly/cleanup.py nightly/notify.py tests/__init__.py tests/test_config.py tests/test_cleanup.py
git commit -q -m "nightly: cleanup with configurable retention"

# Four days ago: retention raised to 30, and the edit left a trailing comma behind.
cat > config/settings.json <<'JSON'
{
  "retention_days": 30,
  "recipients": ["ops@example.com"],
}
JSON
stamp="$(python3 -c 'import datetime; print((datetime.datetime.now().astimezone() - datetime.timedelta(days=4)).replace(microsecond=0).isoformat())')"
git add config/settings.json
GIT_AUTHOR_DATE="$stamp" GIT_COMMITTER_DATE="$stamp" git commit -q -m "settings: keep files for 30 days"
