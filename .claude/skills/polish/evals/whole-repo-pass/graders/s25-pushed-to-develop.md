---
# S25 (SKILL.md:95), S10 (SKILL.md:38): the push lands on develop, the branch noted in phase 1, never a new branch (the remote's post-receive hook logs the ref)
type: regex
pattern: 'push refs/heads/develop'
target: { source: file, path: .eval/pushes.log }
match: contains
---
