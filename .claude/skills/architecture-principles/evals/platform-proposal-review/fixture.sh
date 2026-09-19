#!/usr/bin/env bash
# A shop run by two teams of four over one Python monolith, one shared Postgres both teams write,
# one React frontend, manual deployments from a release branch every six weeks, three approvals
# per pull request, a change board, a separate QA team and no WIP limit. The proposal under review
# wants 14 gRPC services on a service mesh over the same shared database, a platform team to run
# them, gitflow, a two-week regression window to raise MTBF, a free stack per service, payments
# generated and maintained by an agent that nobody reads, no staging, and plain HTTP inside.
# Last quarter's tickets show 21- and 34-point work started in June and still open. No
# environment: git, coreutils, python3.
set -euo pipefail
git -c init.defaultBranch=develop init -q
git config user.email mara@example.com
git config user.name "Mara Vogt"
git config commit.gpgsign false
mkdir -p app/checkout app/catalog app/shared frontend/src docs data deploy
touch app/__init__.py app/checkout/__init__.py app/catalog/__init__.py app/shared/__init__.py
printf '__pycache__/\nnode_modules/\n' > .gitignore

cat > README.md <<'MD'
# shop

One Python deployable (`app/`), one Postgres, one React frontend (`frontend/`). Two teams:
Checkout and Catalog, see `docs/team.md`. Deployed by hand from the release branch, see
`deploy/runbook.md`.
MD

cat > docs/team.md <<'MD'
# Teams

- Checkout team (4): Ben (lead), Priya, Tom, Lea. Owns cart, orders, payments, refunds, shipping.
- Catalog team (4): Mara (lead), Jonas, Sam, Ines. Owns products, pricing, promotions, search,
  inventory.
- Architect: Viktor, reviews every pull request.
- QA team (2): Anna, Ola. Test each release candidate for two weeks.
- Release manager: Ola. Ops: Ben, because he knows the servers.

Both teams work in the same repository, write the same database and commit to the same React
application. Last quarter (June to August) both teams together finished three features.
MD

cat > app/shared/db.py <<'PY'
import os

DATABASE_URL = os.environ.get("DATABASE_URL", "postgres://shop@localhost/shop")

# Both teams read and write every table through this one connection factory.
TABLES = ["customers", "carts", "orders", "payments", "refunds", "products", "prices",
          "promotions", "inventory", "shipments"]


def connect():
    raise NotImplementedError("wired to psycopg in production")
PY

cat > app/checkout/orders.py <<'PY'
from app.catalog import inventory, pricing, promotions
from app.shared import db


def place_order(cart):
    conn = db.connect()
    total = 0
    for sku, quantity in cart["lines"]:
        unit = pricing.unit_price(conn, sku)
        unit = promotions.apply(conn, sku, unit)
        inventory.reserve(conn, sku, quantity)
        total += unit * quantity
    conn.execute("INSERT INTO orders (customer_id, total) VALUES (%s, %s)", (cart["customer"], total))
    conn.execute("UPDATE products SET last_ordered = now() WHERE sku = ANY(%s)", ([s for s, _ in cart["lines"]],))
    return total
PY

cat > app/catalog/pricing.py <<'PY'
def unit_price(conn, sku):
    row = conn.execute("SELECT cents FROM prices WHERE sku = %s", (sku,)).fetchone()
    return row[0]
PY

cat > app/catalog/promotions.py <<'PY'
def apply(conn, sku, cents):
    row = conn.execute("SELECT percent FROM promotions WHERE sku = %s", (sku,)).fetchone()
    return cents if row is None else cents * (100 - row[0]) // 100
PY

cat > app/catalog/inventory.py <<'PY'
def reserve(conn, sku, quantity):
    conn.execute("UPDATE inventory SET stock = stock - %s WHERE sku = %s", (quantity, sku))
    conn.execute("UPDATE orders SET reserved = true WHERE sku = %s", (sku,))
PY

cat > frontend/package.json <<'JSON'
{
  "name": "shop-frontend",
  "version": "3.8.0",
  "private": true,
  "dependencies": { "react": "^18.3.0", "react-router-dom": "^6.26.0" }
}
JSON

cat > frontend/src/App.js <<'JS'
import { Routes, Route } from "react-router-dom";
import Cart from "./checkout/Cart";
import Checkout from "./checkout/Checkout";
import Orders from "./checkout/Orders";
import Catalog from "./catalog/Catalog";
import Product from "./catalog/Product";
import Search from "./catalog/Search";

// Both teams commit here; the frontend guild reviews every change.
export default function App() {
  return (
    <Routes>
      <Route path="/" element={<Catalog />} />
      <Route path="/p/:sku" element={<Product />} />
      <Route path="/search" element={<Search />} />
      <Route path="/cart" element={<Cart />} />
      <Route path="/checkout" element={<Checkout />} />
      <Route path="/orders" element={<Orders />} />
    </Routes>
  );
}
JS

cat > CODEOWNERS <<'TXT'
# Every path needs an approval from each of the three.
*  @ben @mara @viktor
TXT

cat > deploy/runbook.md <<'MD'
# Release runbook

Run every six weeks after QA signs off the release branch. Ben runs it; Ola watches.

1. Announce the freeze in #engineering.
2. `git checkout release/x.y` on the build box.
3. Bump the version in `app/version.py` and `frontend/package.json` by hand.
4. `pip install -r requirements.txt` and `npm ci`.
5. `npm run build`, copy `frontend/build` to `/srv/shop/static`.
6. Stop the app: `systemctl stop shop` on web-1, web-2, web-3, in that order.
7. `rsync app/ /srv/shop/app` on each box.
8. Run the migrations from `migrations/` by hand, in order, on the primary.
9. Start web-1, warm the pricing cache (ask Ben for the command).
10. Check the health page; if red, restore last week's rsync snapshot and restart.
11. Start web-2 and web-3.
12. Update the DNS weight in the load balancer console.
13. Post the release notes in #announcements.
14. Close the change board ticket.
Rollback: repeat from step 2 with the previous release branch, about four hours.
MD

cat > docs/process.md <<'MD'
# How we work

- Branches: feature branches off `develop`; a release branch is cut every six weeks; hotfixes
  off the release branch.
- Every pull request needs three approvals: both team leads and the architect (`CODEOWNERS`).
  Median time to first approval last quarter: 3.5 days.
- A ticket moves dev -> QA -> release manager -> ops. QA tests the release candidate for two
  weeks. The change board (CTO, architect, both leads, QA lead) meets Thursdays and approves
  the release.
- Estimation: an epic is one ticket, points up to 34. No limit on how many tickets a person has
  in progress.
- Recurring meetings per week: daily standup (both teams together, 45 minutes), backlog
  refinement (2x), sprint planning, sprint review, retro, architecture guild, frontend guild,
  change board, release readiness, incident review, all-hands. Eleven in all.
- Bugs from production go straight into the running sprint.
MD

cat > docs/oncall-notes.md <<'MD'
# On-call notes, August

- Aug 2, 02:40. Pricing cache cold after the release; checkout timed out for 50 minutes. Ben
  warmed it by hand. Nobody else knows the command.
- Aug 14, 03:10. Deploy of 3.7.2 left web-2 on the old build. Ben fixed it from his phone.
  Third night this month, thanks Ben, drinks are on the company on Friday.
- Aug 21. Mara's search change was reverted because the same deploy carried Tom's refund
  change, which broke; both went back.
- Aug 29, 23:55. Inventory reserved twice for the same order; Ben patched the row in the
  database directly. Ticket SHOP-341 opened, unplanned.
MD

cat > docs/proposal-platform-2027.md <<'MD'
# Platform 2027

Author: Viktor (architect). Budget request: EUR 1.4M over 14 months.

## 1. Service decomposition

The monolith becomes 14 independently deployable services: cart, checkout, orders,
order-history, payments, refunds, shipping, customers, products, pricing, promotions, search,
inventory, notifications. The two product teams share them per the ownership matrix in the
appendix (Checkout team: 7 services, Catalog team: 7 services).

## 2. Communication

All services talk gRPC with protobuf contracts, through a service mesh with sidecars for
retries, timeouts and tracing. Checkout calls pricing, which calls promotions, which calls
inventory, which calls shipping for the quote, within one request, so the customer sees a
consistent total. The existing Postgres stays as the integration database that every service
reads and writes; no data migration is needed.

## 3. Reliability

Target: raise the mean time between failures from 9 days to 30. Each release gets a two-week
regression window run by QA, a manual sign-off checklist per service, and the change board's
approval. Rollback stays as it is today: rebuild the previous release branch, about four hours.

## 4. Delivery

Gitflow across all repositories: feature branches, develop, a release branch cut every six
weeks, hotfix branches. Releases are deployed by the platform team from the runbook.

## 5. Frontend

One React application that both teams commit to, with a shared component library. The frontend
guild reviews every pull request to it.

## 6. Ownership

A new platform team of three runs all 14 services in production and carries on-call. The
product teams hand over at release and stay on feature work.

## 7. Technology choice

Each service chooses its own stack. Catalog wants Kotlin and MongoDB for search and Elixir for
pricing; Checkout wants Node for cart and Go for payments.

## 8. AI

Payments and refunds are generated and maintained by the coding agent from a written spec.
Engineers review the acceptance tests only; nobody needs to read the generated code. This frees
two engineers for feature work.

## 9. Environments

Staging is decommissioned (EUR 2,100 a month). QA tests on production behind feature flags.

## 10. Security

TLS terminates at the load balancer. Traffic between services is plain HTTP to keep latency
low; mutual TLS is a phase 3 item.

## Timeline

Phase 1 (months 1-6): mesh, contracts, platform team hired. Phase 2 (months 7-12): extraction
of the 14 services. Phase 3 (months 13-14): mTLS, observability, hand-over.
MD

cat > data/tickets.csv <<'CSV'
id,team,title,points,started,finished,status
SHOP-301,checkout,Refund flow rewrite,34,2026-06-02,,in progress
SHOP-302,checkout,Saved payment methods,21,2026-06-03,,in progress
SHOP-303,checkout,Cart merge on login,13,2026-06-09,2026-08-20,done
SHOP-304,checkout,Address validation,8,2026-06-16,,waiting for QA
SHOP-305,checkout,Gift cards,21,2026-06-23,,in progress
SHOP-306,checkout,Order tracking page,13,2026-07-01,,waiting for release
SHOP-307,checkout,Split shipments,21,2026-07-14,,in progress
SHOP-308,checkout,Hotfix double reservation,3,2026-08-30,2026-08-31,done
SHOP-321,catalog,Search relevance v2,34,2026-06-01,,in progress
SHOP-322,catalog,Bulk price import,13,2026-06-08,2026-07-30,done
SHOP-323,catalog,Promotion scheduling,21,2026-06-15,,in progress
SHOP-324,catalog,Product variants,34,2026-06-22,,in progress
SHOP-325,catalog,Inventory sync with warehouse,21,2026-07-06,,waiting for QA
SHOP-326,catalog,Category landing pages,13,2026-07-20,2026-08-28,done
SHOP-327,catalog,Search autocomplete,8,2026-08-03,,in progress
SHOP-328,catalog,Price history,13,2026-08-10,,in progress
SHOP-341,catalog,Unplanned: inventory reserved twice,5,2026-08-30,,in progress
SHOP-342,checkout,Unplanned: web-2 stale build after deploy,2,2026-08-15,2026-08-15,done
CSV

git add .gitignore README.md CODEOWNERS app/__init__.py app/checkout/__init__.py app/catalog/__init__.py app/shared/__init__.py app/shared/db.py app/checkout/orders.py app/catalog/pricing.py app/catalog/promotions.py app/catalog/inventory.py frontend/package.json frontend/src/App.js deploy/runbook.md docs/team.md docs/process.md docs/oncall-notes.md docs/proposal-platform-2027.md data/tickets.csv
git commit -q -m "shop: current system, process notes and the platform 2027 proposal"
