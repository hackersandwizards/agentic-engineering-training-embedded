---
name: trace-culina-context
description: Trace a Culina protocol, safety or control claim from its authoritative engineering source into implementation and verification. Use before planning changes in src/protocol, src/mcu or safety-related application code.
allowed-tools: Read, Grep, Glob, Bash
---

# Trace Culina context

1. Identify the authoritative source in `docs/` for the requested claim.
2. Trace the claim into implementation and existing tests with exact file and
   line references.
3. Mark each conclusion confirmed, ambiguous or unsupported.
4. Report which host, simulator or physical-product evidence is still missing.
5. Do not edit files or use Git history as an answer source.
