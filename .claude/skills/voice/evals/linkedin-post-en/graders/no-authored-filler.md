---
# T44, T45, T20 (prose-style.md:88-102; personal-voice.md:117-118): the filler list is banned in authored prose, `honestly` never
type: regex
target: { source: file, path: post.md }
match: not_contains
flags: i
---
\b(actually|basically|essentially|really|quite|somewhat|just|simply|sort of|kind of|very|totally|literally|obviously|of course|indeed|in fact|perhaps|maybe|honestly|in my opinion|it should be noted|it is important to)\b|\brather\b(?! than)
