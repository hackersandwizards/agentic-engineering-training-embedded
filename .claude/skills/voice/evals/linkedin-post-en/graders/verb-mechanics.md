---
type: llm
focus: { source: file, path: post.md }
---
# T40, T41, T57 (prose-style.md:15-27; ai-tells.md:51-54): strong verbs, active voice, one name per thing
FAIL if the post carries any of these three:
1. A stretched verb: "made a decision" for "decided", "performed a measurement" for "measured".
2. A passive where the actor matters: "nine PRs were merged" for "the team merged nine PRs". A passive whose actor does not matter ("40 developers surveyed", "the foundation being poured") is not one.
3. Synonym hopping for one referent: "the squad", "the crew", "the engineers" for the team, or "the tools", "the bots" for the agents. The team stays "the team", the agents stay "agents".
Otherwise PASS.
