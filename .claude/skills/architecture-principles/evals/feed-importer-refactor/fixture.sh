#!/usr/bin/env bash
# A Python CSV importer organised by execution step (step1_read, step2_check, step3_write), each
# step indexing the same column layout, wrapped by an ImportService whose methods only forward
# to the steps. util/strings.py holds one-line wrappers over str methods, util/db.py forwards to
# cursor.execute, the CLI opens the database and hands the cursor down, and the general row writer
# carries the promo special case inside it. Tests drive the CLI entry point, so the internals are
# free to move. No environment: git, coreutils, python3.
set -euo pipefail
git -c init.defaultBranch=main init -q
git config user.email mara@example.com
git config user.name "Mara Vogt"
git config commit.gpgsign false
mkdir -p importer/util tests feeds
touch importer/__init__.py importer/util/__init__.py tests/__init__.py
printf '__pycache__/\n*.db\n' > .gitignore

cat > README.md <<'MD'
# importer

Loads supplier product feeds (CSV) into the catalog database (SQLite).

    python3 -m importer feeds/spring.csv catalog.db

Feed columns: `sku,name,price,currency,stock`. Rows whose sku starts with `PROMO-` are
promotions: the price column holds the discount percent and stock is empty. Tests:
`python3 -m unittest`.
MD

cat > importer/__main__.py <<'PY'
import sys

from importer.cli import main

sys.exit(main(sys.argv[1:]))
PY

cat > importer/cli.py <<'PY'
import sqlite3
import sys

from importer.service import ImportService
from importer.step1_read import Reader
from importer.step2_check import Checker
from importer.step3_write import Writer


def main(argv):
    if len(argv) != 2:
        print("usage: python3 -m importer FEED.csv CATALOG.db", file=sys.stderr)
        return 2
    path, db = argv
    # open the database
    conn = sqlite3.connect(db)
    cursor = conn.cursor()
    service = ImportService(Reader(), Checker(), Writer())
    tmp = service.read(path)
    info = service.check(tmp)
    n = service.write(info, cursor)
    conn.commit()
    conn.close()
    print(f"imported {n} rows")
    return 0
PY

cat > importer/service.py <<'PY'
class ImportService:
    def __init__(self, reader, checker, writer):
        self.reader = reader
        self.checker = checker
        self.writer = writer

    def read(self, path):
        return self.reader.read(path)

    def check(self, rows):
        return self.checker.check(rows)

    def write(self, rows, cursor):
        return self.writer.write(rows, cursor)
PY

cat > importer/step1_read.py <<'PY'
import csv

from importer.util.strings import trim

HEADER = ["sku", "name", "price", "currency", "stock"]


class Reader:
    def read(self, path):
        with open(path, newline="") as handle:
            rows = list(csv.reader(handle))
        if rows and rows[0] == HEADER:
            rows = rows[1:]
        return [[trim(cell) for cell in row] for row in rows]
PY

cat > importer/step2_check.py <<'PY'
from importer.util.strings import is_blank, lower

CURRENCIES = {"eur", "usd", "chf"}


class Checker:
    def check(self, rows):
        out = []
        for row in rows:
            if len(row) != 5:
                raise ValueError(f"row has {len(row)} columns, expected 5")
            if is_blank(row[0]):
                raise ValueError("row without sku")
            if row[0].startswith("PROMO-"):
                if not row[2].isdigit():
                    raise ValueError(f"promo {row[0]}: percent must be an integer")
            else:
                if lower(row[3]) not in CURRENCIES:
                    raise ValueError(f"row {row[0]}: unknown currency {row[3]}")
                if not row[4].isdigit():
                    raise ValueError(f"row {row[0]}: stock must be an integer")
            out.append(row)
        return out
PY

cat > importer/step3_write.py <<'PY'
from importer.util.db import run

PRODUCTS = (
    "CREATE TABLE IF NOT EXISTS products "
    "(sku TEXT PRIMARY KEY, name TEXT, price_cents INTEGER, currency TEXT, stock INTEGER)"
)
PROMOTIONS = "CREATE TABLE IF NOT EXISTS promotions (code TEXT PRIMARY KEY, name TEXT, percent INTEGER)"


class Writer:
    def write(self, rows, cursor):
        run(cursor, PRODUCTS, ())
        run(cursor, PROMOTIONS, ())
        # set counter to zero
        count = 0
        for row in rows:
            if row[0].startswith("PROMO-"):
                run(
                    cursor,
                    "INSERT OR REPLACE INTO promotions VALUES (?, ?, ?)",
                    (row[0], row[1], int(row[2])),
                )
            else:
                run(
                    cursor,
                    "INSERT OR REPLACE INTO products VALUES (?, ?, ?, ?, ?)",
                    (row[0], row[1], int(round(float(row[2]) * 100)), row[3].upper(), int(row[4])),
                )
            # increment counter
            count += 1
        return count
PY

cat > importer/util/strings.py <<'PY'
def trim(s):
    return s.strip()


def lower(s):
    return s.lower()


def is_blank(s):
    return s.strip() == ""
PY

cat > importer/util/db.py <<'PY'
def run(cursor, sql, params):
    return cursor.execute(sql, params)
PY

cat > feeds/spring.csv <<'CSV'
sku,name,price,currency,stock
A-100,Garden hose 20m,19.90,eur,12
B-200,Electric mower,149.00,EUR,3
PROMO-SPRING,Spring sale,15,,
CSV

cat > tests/test_importer.py <<'PY'
import contextlib
import io
import os
import sqlite3
import tempfile
import unittest

from importer.cli import main

FEED = os.path.join(os.path.dirname(os.path.dirname(__file__)), "feeds", "spring.csv")


def run_cli(feed, db):
    out = io.StringIO()
    with contextlib.redirect_stdout(out):
        code = main([feed, db])
    return code, out.getvalue()


class ImporterTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.db = os.path.join(self.tmp.name, "catalog.db")

    def tearDown(self):
        self.tmp.cleanup()

    def rows(self, sql):
        with sqlite3.connect(self.db) as conn:
            return conn.execute(sql).fetchall()

    def test_products_land_with_cents_and_upper_currency(self):
        code, out = run_cli(FEED, self.db)
        self.assertEqual(code, 0)
        self.assertEqual(out.strip(), "imported 3 rows")
        self.assertEqual(
            self.rows("SELECT sku, price_cents, currency, stock FROM products ORDER BY sku"),
            [("A-100", 1990, "EUR", 12), ("B-200", 14900, "EUR", 3)],
        )

    def test_promo_rows_land_in_promotions(self):
        run_cli(FEED, self.db)
        self.assertEqual(self.rows("SELECT code, percent FROM promotions"), [("PROMO-SPRING", 15)])

    def test_reimport_is_idempotent(self):
        run_cli(FEED, self.db)
        run_cli(FEED, self.db)
        self.assertEqual(self.rows("SELECT count(*) FROM products"), [(2,)])

    def test_unknown_currency_is_rejected(self):
        feed = os.path.join(self.tmp.name, "bad.csv")
        with open(feed, "w") as handle:
            handle.write("sku,name,price,currency,stock\nC-300,Rake,9.90,gbp,4\n")
        with self.assertRaises(ValueError):
            run_cli(feed, self.db)

    def test_usage_error(self):
        with contextlib.redirect_stderr(io.StringIO()):
            self.assertEqual(main([FEED]), 2)


if __name__ == "__main__":
    unittest.main()
PY

git add .gitignore README.md importer/__init__.py importer/__main__.py importer/cli.py importer/service.py importer/step1_read.py importer/step2_check.py importer/step3_write.py importer/util/__init__.py importer/util/strings.py importer/util/db.py feeds/spring.csv tests/__init__.py tests/test_importer.py
git commit -q -m "importer: three-step feed import into the catalog"
