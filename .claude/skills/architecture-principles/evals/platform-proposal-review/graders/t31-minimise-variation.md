---
# T31 (SKILL.md:31,45): sensible defaults and minimal variation, so the review rejects a free stack per service
type: regex
pattern: 'radar|sensible defaults?|standardi[sz]|minimi[sz]e variation|(?:one|a single|the same|a shared|a common) (?:stack|language|runtime|platform)|freedom within constraints|(?:five|5|six|6|seven|7) (?:languages|stacks|runtimes)|too many (?:languages|stacks|technologies)|polyglot'
flags: i
target: { source: file, path: docs/review-platform-2027.md }
match: contains
weight: 1
---
