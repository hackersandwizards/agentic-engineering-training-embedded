---
# M4: the one comment stating a fact the code cannot (bank exports repeat the last row of a page) survives, and the code is unchanged
type: llm
focus: { source: file, path: ledger/parse.py }
weight: 2
---
Read the file. PASS only if all hold:
1. A comment in parse_lines still explains that bank exports repeat the last row of each page, which is why rows are deduplicated. Rewording is fine as long as the page-repeat reason is stated.
2. No remaining comment restates what the adjacent line of code does.
3. The functions parse_line and parse_lines, the LINE regex and SORT_KEY still exist and their logic is the same: strip, blank returns None, no match raises ValueError, groups returned with float amount, dedupe, sort by date.
FAIL if the page-repeat fact was deleted, if noise comments remain, or if the code was rewritten beyond comment changes.
