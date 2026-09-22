# Minimalism

Write the laziest solution that works, in code, in instruction artifacts (skills, agents, rules,
prompts) and in any document. Say the least that fully does the job, then stop.

**The ladder.** Stop at the first rung that holds:

1. Does this need to exist at all? If speculative, skip it and say so. Where the omission fails
   silently, as a missing allowlist entry or fail-closed guard does, include it and name why.
2. Standard library does it? Use it.
3. Native platform feature covers it? Use it.
4. An installed dependency solves it? Use it. Never add one for what a few lines do.
5. Can it be one line? One line.
6. Only then: the minimum code that works.

**Rules:**

- Deliver the requested scope, without cleanup, refactoring, documentation or an adjacent feature.
- No interface, factory or config for a single case, and no scaffolding for later.
- Change what exists by removal first, then replacement, then addition. Where a removal drops a
  rule you still want, replace it.
- Fewest files possible. The shortest working diff wins.
- One owner per fact or rule: state it once, in the file that owns it, and point there. This stops
  at a skill's edge: a skill's files point only at that skill's own files and at the repository data
  and scripts it acts on, never at another skill, rule, agent or memory file. A skill whose subject
  is the inventory of those artifacts may name them in the rows it catalogs, and no other skill
  cites such a row ID. Redundancy between skills is the price of that independence.
- A list whose gaps read as answers keeps a row that restates its owner where the missing row would
  say "nothing is needed here". Where it would send the reader elsewhere, the row goes.
- Cut a line a capable model follows without it, one whose case never arises or would announce
  itself, and one restating what a system of record provides. That test reads on a rule, never on a
  record. A line preserving something observed, a measured number, a verbatim phrasing, how a
  particular person sounds, stays: without it the model invents a plausible substitute.

**Output:** name what you left out and when adding it becomes worth it. For a complex request, ship
the lazy version and question the rest in the same response. Never stall on an answer you can
default.
