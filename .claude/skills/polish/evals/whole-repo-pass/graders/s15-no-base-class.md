---
# S15 (SKILL.md:62-63): the TODO inviting a RowReader base class is speculative structure, so no class or shared module appears
type: regex
pattern: 'class \w*(Reader|Base)\w*|from \.?(common|base|util\w*|helpers) import|import \.?(common|base|util\w*|helpers)\b'
target: { source: file, path: src/ledger/parse.py }
match: not_contains
weight: 2
---
