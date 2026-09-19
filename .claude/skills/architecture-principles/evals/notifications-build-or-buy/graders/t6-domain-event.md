---
# T6 (SKILL.md:38-39): contexts communicate through domain events, so notifications react to an order event instead of an inline call or a polled shared table
type: llm
focus: { source: file, path: docs/adr/0004-customer-notifications.md }
weight: 2
---
Read how the decided design connects the order flow to the sending of a notification. PASS if a status change is published as a domain event (an in-process event or handler, an outbox table owned by the publisher and drained by a handler, or an event stream) that the notification code subscribes to. FAIL if orders.py or the order flow calls the notification code or the provider directly inline as one more step, or if another process polls a table both sides read and write; also FAIL if the ADR does not say how the two are connected.
