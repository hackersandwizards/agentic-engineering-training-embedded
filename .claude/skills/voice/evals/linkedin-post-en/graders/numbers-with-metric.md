---
# T76, T161 (brand-voice.md:99-102; brand-vocabulary.md:60-63): every number names what it measures
# A paragraph that carries a digit and no metric noun (PRs, weeks, lines, developers, people, hours, days, months, minutes, tests, bugs, deploys, incidents, users, customers, teams, engineers, commits, merges, releases, agents, tickets, features, files, tokens, EUR, `of N`) fails, as do `order of magnitude` and `productivity went up`. The `(Source: ...)` line is exempt
type: regex
target: { source: file, path: post.md }
match: not_contains
flags: i
---
(^|\n)(?!\(Source:)(?![^\n]*\b(?:PRs?|weeks?|lines?|developers?|people|persons?|hours?|days?|months?|years?|minutes?|seconds?|ms|tests?|bugs?|deploys?|deployments?|incidents?|users?|customers?|teams?|engineers?|commits?|merges?|releases?|agents?|tickets?|features?|files?|tokens?|EUR|€|\$|per cent|of \d+)\b)[^\n]*\d|\border of magnitude\b|\bproductivity went up\b
