---
# T17 (SKILL.md:53): a special-general mixture is a red flag, so the report says the promo rows are handled apart from the general product writer
type: llm
focus: last_message
weight: 1
---
Before the change, the general row writer branched inside its loop on skus starting with PROMO- to write a promotions row instead of a products row, and the checker branched the same way. FAIL if the report does not say the promotion rows are now handled by their own function, class or module, separated from the product path, or if it says the branch inside the general writer was kept; otherwise PASS.
