#!/usr/bin/env bash
# A small Python shop package. tests/test_reports.py names the reports module in its file name
# but half its cases exercise shop/money.py, which shop/invoices.py still uses. Deleting the
# reports feature deletes that test file; the money cases must be ported, not lost.
set -euo pipefail
git -c init.defaultBranch=main init -q
git config user.email mara@example.com
git config user.name "Mara Vogt"
git config commit.gpgsign false

mkdir -p shop tests
touch shop/__init__.py tests/__init__.py

cat > shop/money.py <<'PY'
from decimal import ROUND_HALF_UP, Decimal


def format_money(cents):
    amount = (Decimal(cents) / 100).quantize(Decimal("0.01"), rounding=ROUND_HALF_UP)
    return f"{amount:,.2f}"


def parse_money(text):
    return int((Decimal(text.replace(",", "")) * 100).to_integral_value(rounding=ROUND_HALF_UP))
PY

cat > shop/invoices.py <<'PY'
from shop.money import format_money


def invoice_lines(items):
    return [f"{name}: {format_money(cents)}" for name, cents in items]


def invoice_total(items):
    return format_money(sum(cents for _name, cents in items))
PY

cat > shop/reports.py <<'PY'
from collections import defaultdict

from shop.money import format_money


def summarize(orders):
    by_customer = defaultdict(int)
    for customer, cents in orders:
        by_customer[customer] += cents
    return {customer: format_money(cents) for customer, cents in sorted(by_customer.items())}


def render(orders):
    return "\n".join(f"{customer} {total}" for customer, total in summarize(orders).items())
PY

cat > shop/cli.py <<'PY'
import sys

from shop.invoices import invoice_lines, invoice_total
from shop.reports import render

COMMANDS = ("invoice", "report")


def main(argv):
    if not argv or argv[0] not in COMMANDS:
        raise SystemExit(f"usage: shop {'|'.join(COMMANDS)}")
    if argv[0] == "invoice":
        items = [("widget", 1999), ("gadget", 250)]
        return "\n".join(invoice_lines(items) + [f"total: {invoice_total(items)}"])
    if argv[0] == "report":
        return render([("acme", 1999), ("beta", 250), ("acme", 1)])


if __name__ == "__main__":
    print(main(sys.argv[1:]))
PY

cat > tests/test_money.py <<'PY'
import unittest

from shop.money import format_money, parse_money


class MoneyTests(unittest.TestCase):
    def test_format_zero(self):
        self.assertEqual(format_money(0), "0.00")

    def test_format_positive(self):
        self.assertEqual(format_money(1999), "19.99")

    def test_parse_round_trip(self):
        self.assertEqual(parse_money("19.99"), 1999)


if __name__ == "__main__":
    unittest.main()
PY

cat > tests/test_reports.py <<'PY'
import unittest

from shop.money import format_money
from shop.reports import render, summarize


class ReportTests(unittest.TestCase):
    def test_summarize_groups_by_customer(self):
        self.assertEqual(summarize([("acme", 1999), ("beta", 250), ("acme", 1)]), {"acme": "20.00", "beta": "2.50"})

    def test_render_one_line_per_customer(self):
        self.assertEqual(render([("acme", 1999)]), "acme 19.99")

    def test_negative_amount_keeps_sign_and_grouping(self):
        self.assertEqual(format_money(-123456), "-1,234.56")

    def test_thousands_separator(self):
        self.assertEqual(format_money(100000000), "1,000,000.00")

    def test_sub_cent_rounds_half_up(self):
        self.assertEqual(format_money(0.5), "0.01")


if __name__ == "__main__":
    unittest.main()
PY

cat > tests/test_cli.py <<'PY'
import unittest

from shop.cli import main


class CliTests(unittest.TestCase):
    def test_invoice(self):
        self.assertEqual(main(["invoice"]).splitlines()[-1], "total: 22.49")

    def test_report(self):
        self.assertEqual(main(["report"]), "acme 20.00\nbeta 2.50")

    def test_unknown_command(self):
        with self.assertRaises(SystemExit):
            main(["nope"])


if __name__ == "__main__":
    unittest.main()
PY

cat > README.md <<'MD'
# shop

`python3 -m shop.cli invoice` prints a sample invoice, `python3 -m shop.cli report` a per-customer report.
Tests: `python3 -m unittest`.
MD

printf '__pycache__/\n' > .gitignore
git add .gitignore README.md shop/__init__.py shop/money.py shop/invoices.py shop/reports.py shop/cli.py tests/__init__.py tests/test_money.py tests/test_reports.py tests/test_cli.py
git commit -q -m "shop: invoices, reports, cli"
