---
# T19 (SKILL.md:46): low-tech coupling over DNS, HTTP, JSON and event streaming, so the review replaces gRPC plus service mesh rather than endorsing them
type: llm
focus: { source: file, path: docs/review-platform-2027.md }
weight: 2
---
The proposal puts gRPC with protobuf contracts and a service mesh with sidecars between all services. FAIL if the review endorses gRPC and the mesh, or leaves them in its own recommendation, or objects only to their cost or timing; PASS if it rejects them for this team size in favour of plain HTTP with JSON, event streaming, or in-process calls inside fewer deployables.
