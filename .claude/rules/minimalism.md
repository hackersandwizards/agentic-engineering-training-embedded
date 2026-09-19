# Minimalism

You write the laziest solution that works, in code, in instruction artifacts (skills, agents,
rules, prompts) and in any document. Say the least that fully does the job, then stop.

**The ladder.** Stop at the first rung that holds:

1. Does this need to exist at all? If speculative, skip it and say so. (YAGNI) YAGNI assumes the
   omission fails loudly. Where it fails silently instead, as a missing allowlist entry or an
   absent fail-closed guard does, the omission is the expensive side: include it and name why.
2. Standard library does it? Use it.
3. Native platform feature covers it? Use it.
4. An installed dependency solves it? Use it. Never add one for what a few lines do.
5. Can it be one line? One line.
6. Only then: the minimum code that works.

**Rules:**

- Deliver the requested scope. Do not widen it into cleanup, refactoring, documentation or an
  adjacent feature.
- No interface, factory or config for a single case.
- No scaffolding for later.
- Change what exists by removal first, then replacement, then addition. Removal that drops a
  rule you still want is not minimal: replace it.
- Fewest files possible. The shortest working diff wins.
- One owner per fact or rule. State it once, in the file or section that owns it, and point there,
  never restated in a second file or section. This stops at a skill's edge: a skill's files point
  only at that same skill's files and at the repository data and scripts it acts on, never at
  another skill, rule, agent or memory file, by link or by name. A skill whose subject matter is
  the inventory of those artifacts is the exception, bounded to the rows it catalogs: naming which
  artifact owns which mechanic is that content, not a dependency on it. The exception runs one
  way only: a row ID of that inventory is such a name, and no other skill cites one. Redundancy
  between skills is the price of that independence. One owner per fact stops again at a list
  whose gaps read as answers. Ask what a missing row would tell a reader. Where it answers
  "nothing is needed here", the row stays though it restates its owner. Where it sends the
  reader looking elsewhere, the row goes.
- Cut a line a capable model follows without it, one whose case never arises or would announce
  itself, and one restating what a system of record already provides: state the principle
  instead. The test, would a capable model do this right without the line, reads on a rule and
  never on a record. A line preserving something observed rather than reasoned, a measured
  number, a verbatim phrasing, how a particular person actually sounds, is not one a capable
  model gets right without it: absent the line it invents a plausible substitute. Cut only what
  has no impact, which is not what unmeasured means.

**Output:** name what you left out or decided against, and when adding it becomes worth it. If
the explanation runs longer than what it explains, cut it. For a complex request, ship the lazy
version and question the rest in the same response. Never stall on an answer you can default.
