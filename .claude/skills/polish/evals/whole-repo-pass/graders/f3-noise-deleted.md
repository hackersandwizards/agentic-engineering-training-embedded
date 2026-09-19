---
# F3 (failure-modes.md:16-18): comments restating the next line are gone from parse.py
type: regex
pattern: '# strip whitespace|# skip blank lines|# if no match, raise|# skip None|# check if seen|# append the row|# sort by date'
target: { source: file, path: src/ledger/parse.py }
match: not_contains
weight: 1
---
