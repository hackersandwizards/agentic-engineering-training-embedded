#!/usr/bin/env bash
# A Python shop monolith run by one product team of five, deployed on every green build. Three
# ADRs record the existing decisions (record decisions, Postgres only, one deployable). Product's
# request for customer notifications carries two competing engineer proposals: a Go service with
# gRPC, NATS and Redis fed by a polled table, or a hosted messaging provider. The order flow calls
# its collaborators synchronously inline, so nothing in the code suggests events. No environment:
# git, coreutils, python3.
set -euo pipefail
git -c init.defaultBranch=main init -q
git config user.email mara@example.com
git config user.name "Mara Vogt"
git config commit.gpgsign false
mkdir -p shop tests docs/adr docs/requests
touch shop/__init__.py tests/__init__.py
printf '__pycache__/\n' > .gitignore

cat > README.md <<'MD'
# shop

The web shop, one Python deployable on top of Postgres. Run the tests with `python3 -m unittest`.
Decisions are recorded under `docs/adr/`.
MD

cat > shop/orders.py <<'PY'
from shop import inventory, payments

ORDERS = {}


class OrderError(Exception):
    pass


def create(order_id, customer_id, lines):
    if order_id in ORDERS:
        raise OrderError(f"order {order_id} exists")
    for sku, quantity in lines:
        inventory.reserve(sku, quantity)
    ORDERS[order_id] = {"customer": customer_id, "lines": list(lines), "status": "created"}
    return ORDERS[order_id]


def pay(order_id, card_token):
    order = ORDERS[order_id]
    total = sum(inventory.price(sku) * quantity for sku, quantity in order["lines"])
    payments.capture(order_id, card_token, total)
    order["status"] = "paid"
    return order


def ship(order_id, tracking_code):
    order = ORDERS[order_id]
    if order["status"] != "paid":
        raise OrderError(f"order {order_id} is {order['status']}, not paid")
    order["status"] = "shipped"
    order["tracking"] = tracking_code
    return order


def deliver(order_id):
    order = ORDERS[order_id]
    order["status"] = "delivered"
    return order
PY

cat > shop/inventory.py <<'PY'
STOCK = {"A-100": 12, "B-200": 3}
PRICES = {"A-100": 19.90, "B-200": 149.00}


class OutOfStock(Exception):
    pass


def reserve(sku, quantity):
    if STOCK.get(sku, 0) < quantity:
        raise OutOfStock(sku)
    STOCK[sku] -= quantity


def price(sku):
    return PRICES[sku]
PY

cat > shop/payments.py <<'PY'
CAPTURED = []


def capture(order_id, card_token, amount):
    CAPTURED.append((order_id, card_token, round(amount, 2)))
    return {"order": order_id, "amount": round(amount, 2)}
PY

cat > shop/customers.py <<'PY'
CUSTOMERS = {
    "c-1": {"email": "ana@example.com", "phone": "+4917000000001", "language": "de"},
    "c-2": {"email": "bo@example.com", "phone": None, "language": "en"},
}


def get(customer_id):
    return CUSTOMERS[customer_id]
PY

cat > tests/test_orders.py <<'PY'
import unittest

from shop import inventory, orders, payments


class OrderFlowTests(unittest.TestCase):
    def setUp(self):
        orders.ORDERS.clear()
        payments.CAPTURED.clear()
        inventory.STOCK.update({"A-100": 12, "B-200": 3})

    def test_create_pay_ship_deliver(self):
        orders.create("o-1", "c-1", [("A-100", 2)])
        orders.pay("o-1", "tok")
        orders.ship("o-1", "TRK1")
        self.assertEqual(orders.deliver("o-1")["status"], "delivered")
        self.assertEqual(payments.CAPTURED, [("o-1", "tok", 39.8)])

    def test_ship_needs_payment(self):
        orders.create("o-2", "c-2", [("B-200", 1)])
        with self.assertRaises(orders.OrderError):
            orders.ship("o-2", "TRK2")


if __name__ == "__main__":
    unittest.main()
PY

cat > docs/team.md <<'MD'
# Team

One product team owns the shop end to end: Mara (lead), Jonas, Lea, Priya, Tom. Python 3.12,
Postgres, one deployable. Trunk-based, every green build deploys, six deploys a day on average.
The team carries its own on-call rotation. External partners (the payment provider, the parcel
carrier) are called over plain HTTP with JSON.
MD

cat > docs/adr/0001-record-architecture-decisions.md <<'MD'
# 1. Record architecture decisions

Date: 2025-02-03

## Status

Accepted

## Context

Decisions were made in chat and lost. New team members could not tell why the system looks the
way it does.

## Decision

Every decision that shapes the system gets a numbered file in this directory with these sections:
Status, Context, Decision, Alternatives considered, Consequences.

## Alternatives considered

- A wiki page per decision: rejected, drifts away from the code.
- No records: rejected, this is what we had.

## Consequences

Writing the decision is part of making it. A pull request that changes the shape of the system
links its ADR.
MD

cat > docs/adr/0002-postgres-as-the-only-datastore.md <<'MD'
# 2. Postgres as the only datastore

Date: 2025-02-10

## Status

Accepted

## Context

Five engineers cannot operate three databases well. Every feature so far fits a relational model.

## Decision

Postgres holds all state. Queues, caches and search use Postgres features until a measured
problem says otherwise.

## Alternatives considered

- Redis for sessions and caches: rejected, a second thing to run for a problem we do not have.
- A document store for the catalog: rejected, the catalog is relational.

## Consequences

One backup, one on-call runbook. A feature needing another store must show the measurement.
MD

cat > docs/adr/0003-one-deployable.md <<'MD'
# 3. One deployable

Date: 2025-03-01

## Status

Accepted

## Context

The shop is one team. Splitting the code into services would split nothing between people.

## Decision

The shop stays one deployable built from one repository, deployed on every green build. Modules
inside it (orders, inventory, payments, customers) keep their own tables and talk through Python
calls.

## Alternatives considered

- Services per module: rejected, one team would run five deployables and coordinate with itself.

## Consequences

Module boundaries are enforced in review, not by the network. This decision is revisited when a
second team owns part of the shop.
MD

cat > docs/requests/customer-notifications.md <<'MD'
# Customer notifications

From: product. Wanted for the Q4 release.

Customers ask where their order is. Support answers 60 tickets a week that an email would have
answered. We want:

1. Transactional email at each order step: confirmed, paid, shipped (with tracking link),
   delivered.
2. SMS on the day of delivery for customers who gave a phone number.
3. Later: marketing campaigns to customer segments, and a dashboard of delivery failures for
   support.

Volume today: about 900 orders a day, so roughly 3,600 emails and 500 SMS a day.

## Proposal A (Jonas): notifications service

A separate notifications service in Go, because the team wants to learn Go and delivery is
latency sensitive. The shop writes a row into a `notifications` table on every status change; the
service polls that table, renders templates from its own Redis, and sends over SMTP and an SMS
gateway. The shop and the service talk gRPC for template previews. NATS between the poller and
the senders so that sending can scale. Estimated eight weeks for the first version with all
three channels, then the campaign tool.

## Proposal B (Lea): hosted provider

A hosted messaging provider (the one our payment provider uses) offers an HTTP API for email and
SMS, hosted templates, a campaign tool with segments, delivery webhooks, and a failure log with a
UI. EUR 340 a month at our volume, EUR 900 with the campaign tool. Lea's worry: lock-in, and the
provider owns our templates.
MD

git add .gitignore README.md shop/__init__.py shop/orders.py shop/inventory.py shop/payments.py shop/customers.py tests/__init__.py tests/test_orders.py docs/team.md docs/adr/0001-record-architecture-decisions.md docs/adr/0002-postgres-as-the-only-datastore.md docs/adr/0003-one-deployable.md docs/requests/customer-notifications.md
git commit -q -m "shop: order flow, three ADRs, the notifications request"
