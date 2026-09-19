---
# T12 (SKILL.md:52): a shallow module is a red flag, so util/strings.py, three one-line wrappers over str methods, is deleted in the final git status
type: regex
pattern: '(?:^|\n)\s*[DR]\S*\s+importer/util/strings\.py'
target: last_message
match: contains
weight: 2
---
