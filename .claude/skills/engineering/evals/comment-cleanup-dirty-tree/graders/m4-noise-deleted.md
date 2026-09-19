---
# M4: comments that restate the code are gone
type: regex
pattern: '# strip whitespace|# skip blank lines|# if no match, raise|# return a tuple|# skip None|# check if seen|# append the row|# sort by date'
target: { source: file, path: ledger/parse.py }
match: not_contains
---
