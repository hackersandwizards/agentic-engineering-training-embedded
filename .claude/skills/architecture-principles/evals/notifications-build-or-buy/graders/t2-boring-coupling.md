---
# T2 (SKILL.md:45-46): low-tech coupling and minimal variation, so the decision adds no gRPC, service mesh, broker, second language or second datastore
type: llm
focus: { source: file, path: docs/adr/0004-customer-notifications.md }
weight: 2
---
The team runs Python on Postgres and calls partners over HTTP with JSON. Read the Decision section. FAIL if the decided design introduces any of gRPC or protobuf, a service mesh, a message broker such as NATS or Kafka, a second programming language, or a datastore other than Postgres for the team's own code; otherwise PASS. Naming one of these under Alternatives as rejected is not introducing it. The hosted provider's own HTTP API and webhooks are not a new technology of the team's.
