---
# T8 (SKILL.md:69-71,83): delivery has no unique business value, so email and SMS sending is bought and the shop keeps deciding what to send when
type: llm
focus: { source: file, path: docs/adr/0004-customer-notifications.md }
weight: 1
---
Read the Decision section. FAIL if the team builds the sending of email or SMS itself (its own SMTP, SMS gateway integration, deliverability handling, templates engine and campaign tool); otherwise PASS. Buying the provider while keeping the choice of which notification fires on which order event in the shop's own code is the expected shape.
