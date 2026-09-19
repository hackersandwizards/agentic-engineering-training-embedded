---
# G2: format_money stays, shop/invoices.py still calls it
type: regex
pattern: 'def format_money'
target: { source: file, path: shop/money.py }
match: contains
---
