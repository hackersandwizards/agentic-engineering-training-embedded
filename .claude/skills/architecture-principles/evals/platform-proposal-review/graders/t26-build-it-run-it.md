---
# T26 (SKILL.md:33): you build it, you run it, so the review rejects a platform team that runs what the product teams built
type: regex
pattern: 'you build it,? you run it|builds? (?:it|a service|the service|them)[^.]{0,40}? runs? (?:it|them)|run(?:s)? what (?:they|it|you) build|teams? (?:that )?(?:own|run|operate)s? (?:what they|their own|the services? they|what it) (?:build|ship|wrote|write)|on[- ]call (?:for|stays with|remains with) (?:the |their )?(?:own |product |building |owning )?(?:code|services?|team)'
flags: i
target: { source: file, path: docs/review-platform-2027.md }
match: contains
weight: 1
---
