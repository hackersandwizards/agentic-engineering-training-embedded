---
name: architecture-principles
description: >-
  The h&w standard for what "good" looks like in client systems. Load when reviewing architecture
  or code structure, making a technical recommendation, choosing between designs, writing a
  proposal or training content that takes a technical position, or diagnosing why an engineering
  organization is slow. Skip for routine implementation inside an existing codebase, where the
  surrounding code is the standard.
---

# Architecture Principles for Client Systems

hackers&wizards brings 20+ years of enterprise engineering experience to every engagement. These
principles come from building, operating, and scaling large-scale systems. They define what
"good" looks like in the systems we help clients build.

## Core Philosophy

- Architecture exists to split work between teams so they can ship independently. If it doesn't serve coordination, it's ornamental.
- Principles over rules in complex environments. You cannot write a rule for every situation. Teach judgment instead.
- Code changeability matters more than code correctness. "It is more important for code to be changeable than that it work."
- The Three Ways: Fast Flow, Fast Feedback, Continuous Learning
- Five Ideals: Locality/Simplicity, Focus/Flow/Joy, Improvement of Daily Work, Psychological Safety, Customer Focus

## Engineering Values

1. **Tech follows Business**: business value drives all technical decisions. A running system with minimal functions is more valuable than discussing concepts.
2. **Move fast, fail fast**: short build-measure-learn cycles, Conway's Law, MTTR over MTBF. Uncertain requirements become clearer when teams build and deploy.
3. **Low technical barriers**: standardization, open standards, knowledge exchange across teams.
4. **Coverage of non-functional aspects**: security, performance, resilience, quality pyramid. React with urgency when problems are detected.
5. **Full ownership and clear responsibility**: you build it, you run it. Everything in production must be owned.
6. **Retained expertise in core technologies**: AI accelerates engineering, it does not transfer architecture ownership or domain accountability. Keep the team able to explain, debug, and evolve its core systems without the agent. Delegate implementation, never understanding.

## Architecture Principles

- **Bounded Contexts and Vertical Systems**: DDD-aligned. Own data, business logic, and UI per context. Communication via domain events.
- **Non-Blocking Communication**: events over synchronous calls. Design for eventual consistency.
- **Small and Simple**: microservices sized to team capacity, not nano-services. Every new service is tech debt until proven otherwise.
- **Evolutionary Architecture**: defer accidental complexity. Sacrificial architecture is a valid pattern. Don't be afraid to throw away and rewrite.
- **Cloud Native**: 12-factor apps, infrastructure as code, immutable deployments.
- **Scale Horizontally**: stateless services, shared-nothing, scale via instances not bigger machines.
- **Continuous Delivery and Deployment**: fully automated pipelines, trunk-based development, deploy on every green build.
- **Sensible Defaults**: technology radar, minimize variation. Freedom within constraints.
- **Use Low-Tech Coupling**: DNS, HTTP, JSON, event streaming. Prefer boring technology that everyone understands.
- **Make Decisions in Public**: RFCs, ADRs, architecture decision records. Document the why, not just the what.
- **Security First**: TLS everywhere, threat modeling, security by default, shift left.

## Further files

- `red-flags.md`: Ousterhout's design smells. Load when reviewing code or an existing design.
- `diagnostics.md`: architecture, process, and systemic failure patterns, plus the build-or-buy
  framework. Load when assessing an organization or making a build-or-buy call.
- `techniques-principles-practices.md`: the three-column decision framework. Load when writing
  training content or a proposal that needs the full vocabulary.

The canonical long-form source lives in the company-os repository under
`src/content/knowledge/software-engineering/`. Read it there when working in that repo and the
short form is not enough.
