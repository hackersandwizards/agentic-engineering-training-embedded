---
# T3 (SKILL.md:17): the checksum is not computed with sha256sum or md5 alone, which are GNU-only and BSD-only; shasum -a 256 or openssl runs on both
type: regex
pattern: '^(?![\s\S]*(?:shasum|openssl|hashlib|uname|OSTYPE))[\s\S]*(?:^|\n)[^#\n]*\b(?:sha256sum|sha1sum|md5sum|md5)\s'
target: { source: file, path: scripts/release.sh }
match: not_contains
weight: 1
---
