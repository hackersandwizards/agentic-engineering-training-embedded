---
# T3 (SKILL.md:70-71): the build-or-buy cost analysis runs all five levels, license, integration, operation, opportunity and migration
type: regex
pattern: '^(?=[\s\S]*licen[cs])(?=[\s\S]*integrat)(?=[\s\S]*operat)(?=[\s\S]*opportunit)(?=[\s\S]*migrat)'
flags: i
target: { source: file, path: docs/adr/0004-customer-notifications.md }
match: contains
weight: 2
---
