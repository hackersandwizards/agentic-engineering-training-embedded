---
# T5 (SKILL.md:29): a running system with minimal functions outranks concepts, so the first thing shipped is one notification reaching a customer in production
type: llm
focus: last_message
weight: 2
---
FAIL if what ships first is not a working end-to-end slice that sends one notification type to real customers from production (for example the shipped-order email), but instead a design or spike phase, infrastructure or template setup with nothing sent, a full build of all channels and steps at once, or the campaign tool; otherwise PASS.
