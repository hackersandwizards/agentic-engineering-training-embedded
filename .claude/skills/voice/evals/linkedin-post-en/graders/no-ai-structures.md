---
# T51, T52, T55, T58, T60, T61 (ai-tells.md:9-28, 44-55, 74-81, 95-125): contrastive reframe, negative parallelism, announced count, landscape opener, banned openers, bridge fillers; the thesis was handed over as "not a failure, it's the foundation" and must not survive in that shape
type: regex
target: { source: file, path: post.md }
match: not_contains
flags: i
---
\bnot just \w|\bnot (a |the )?failure\b|it'?s not (just |about |a |an |the )?[^.,\n]{1,40}, (it'?s|but)|isn'?t (just |about |a |an |the )?[^.,\n]{1,40}, (it'?s|but)|\bno \w+, no \w+, (just|only)|in today'?s|in a world where|have you ever wondered|let'?s be honest|here'?s the thing|most people (think|believe|assume)|stop \w+ing\. start|I used to think|whether you'?re a|at the end of the day|in a nutshell|\bultimately\b|in other words|the reality is|to be clear|at its core|when it comes to|on the other hand|that said|at the same time|it'?s worth noting|needless to say|moving forward|\bfurthermore\b|\bmoreover\b|in conclusion|spoiler:|plot twist|(three|two|four|five|a few) (things|points|lessons|takeaways|reasons)( I| to| that)?[:.]|here are (some|a few|three)
