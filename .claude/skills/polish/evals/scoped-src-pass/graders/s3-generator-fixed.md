---
# S3 (SKILL.md:19-20): the generator's template is fixed too, or the next tools/gen_readme.py run restores the false sentence
type: regex
pattern: 'integer cents'
target: { source: file, path: tools/readme.tmpl }
match: not_contains
weight: 2
---
