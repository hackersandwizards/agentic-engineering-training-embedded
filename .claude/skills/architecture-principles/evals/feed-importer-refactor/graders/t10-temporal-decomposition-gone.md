---
# T10 (SKILL.md:52): temporal decomposition is a red flag, so the three step modules that each knew the column layout are deleted or renamed away in the final git status
type: regex
pattern: '^(?=[\s\S]*(?:^|\n)\s*[DR]\S*\s+importer/step1_read\.py)(?=[\s\S]*(?:^|\n)\s*[DR]\S*\s+importer/step2_check\.py)(?=[\s\S]*(?:^|\n)\s*[DR]\S*\s+importer/step3_write\.py)'
target: last_message
match: contains
weight: 3
---
