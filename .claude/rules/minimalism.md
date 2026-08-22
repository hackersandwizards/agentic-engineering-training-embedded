# Minimalism

You write the laziest solution that works. Lazy means efficient, not careless. This governs
everything you author: code, instruction-artifacts (skills, agents, rules, prompts), and any
document you produce. Say the least that fully does the job, then stop.

**The ladder.** Stop at the first rung that holds:

1. Does this need to exist at all? If speculative, skip it and say so. (YAGNI) YAGNI assumes the
   omission fails loudly. Where it fails silently instead, as a missing allowlist entry or an
   absent fail-closed guard does, the omission is the expensive side: include it and name why.
2. Standard library does it? Use it.
3. Native platform feature covers it? `<input type="date">` over a picker lib, CSS over JS, a DB
   constraint over app code.
4. An already-installed dependency solves it? Use it. Never add a new dependency for what a few
   lines can do.
5. Can it be one line? One line.
6. Only then: the minimum code that works.

When two rungs work, take the higher one and stop.

**Rules:**

- No unrequested abstractions: no interface with one implementation, no factory for one product, no
  config for a value that never changes.
- No boilerplate or scaffolding for later. Later can scaffold for itself.
- Changing something that exists: removal first, then replacement, then addition. Removal that
  drops a rule you still want is not minimal, so replace it instead. Boring over clever.
- Fewest files possible. The shortest working diff wins.
- One owner per fact or rule. State it once, in the file or section that owns it, and point there;
  never restate it in a second file or a second section. **This holds within a skill and stops at
  its edge.** A skill's files point at files of that same skill and at the repository data and
  scripts it acts on, and at nothing else under `.claude/`: no other skill, rule, agent or memory
  file, by link or by name. Redundancy between skills is the price of that independence.
- Cut any rule the model already follows by default, that never fires, or that guards a case which
  hasn't happened and would announce itself when it does. The test: would a capable model do this
  right without the line? If yes, cut it,
  and state the principle rather than re-encode what the model or a system of record already
  provides.

**Output:** name what you skipped and when to add it. If the explanation runs longer than what it
explains, cut it. For a complex request, ship the lazy version and question the rest in the same
response. Never stall on an answer you can default.
