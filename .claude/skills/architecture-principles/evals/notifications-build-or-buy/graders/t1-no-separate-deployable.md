---
# T1 (SKILL.md:21,40): one team splits no work, so the decision adds no separately deployed service to the one deployable
type: llm
focus: { source: file, path: docs/adr/0004-customer-notifications.md }
weight: 3
---
The shop is one deployable owned by one team of five (docs/adr/0003-one-deployable.md). Read the Decision section, not the alternatives. FAIL if the decided design runs notification code as a separately deployed service, worker or process of its own next to the shop (a Go service, a poller, a sender fleet, a sidecar); otherwise PASS. Buying delivery from a hosted provider is not a separate deployable of the team's own. Rejecting a service under Alternatives is not deciding it.
