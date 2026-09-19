---
# T16 (SKILL.md:52): information leakage is a red flag, so the report says the column layout is now parsed in one place and the rest works on a parsed record
type: llm
focus: last_message
weight: 2
---
Before the change, the feed's column layout (sku, name, price, currency, stock) was indexed positionally in the reader, the checker and the writer, so a format change touched every file. FAIL if the report does not say that the layout is now defined or parsed in one place, with the other code working on a parsed record (a dataclass, a named tuple, a dict with named fields or equivalent) instead of positional indexes; otherwise PASS.
