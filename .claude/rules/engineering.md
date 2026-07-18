# Engineering

Favor simple, clean, maintainable solutions. Readability and changeability are primary. Small functions, single responsibility. Build against real systems; reserve mocks for isolated test seams. Verify integration points, APIs, and libraries exist before building on them.

## Minimalism

You write the laziest solution that works. Lazy means efficient, not careless. The best artifact is the one never written. This governs everything you author: code, instruction-artifacts (skills, agents, rules, prompts), and any document you produce. An instruction is code, and an always-loaded rule is paid every turn. Say the least that fully does the job, then stop.

**The ladder.** Stop at the first rung that holds:

1. Does this need to exist at all? If speculative, skip it and say so. (YAGNI)
2. Standard library does it? Use it.
3. Native platform feature covers it? `<input type="date">` over a picker lib, CSS over JS, a DB constraint over app code.
4. An already-installed dependency solves it? Use it. Never add a new dependency for what a few lines can do.
5. Can it be one line? One line.
6. Only then: the minimum code that works.

When two rungs work, take the higher one and stop.

**Rules:**

- No unrequested abstractions: no interface with one implementation, no factory for one product, no config for a value that never changes.
- No boilerplate or scaffolding for later. Later can scaffold for itself.
- Deletion over addition. Boring over clever. Clever is what someone decodes at 3am.
- Fewest files possible. The shortest working diff wins.
- When two stdlib options are the same size, take the one that is correct on edge cases.
- One owner per rule. Point to the owner; never state the same guidance in two files.
- Cut any rule the model already follows by default, that never fires, or that guards a case which hasn't happened. It costs tokens every turn and dilutes the rules that matter.

**Output:** code first, then at most three short lines: what was skipped, when to add it. If the explanation runs longer than the code, cut it. For a complex request, ship the lazy version and question the rest in the same response. Never stall on an answer you can default.

**When not to be lazy.** Never simplify away: input validation at trust boundaries, error handling that prevents data loss, security measures, accessibility basics. Work that doesn't warrant full TDD still leaves one runnable check behind: the smallest thing that fails if the logic breaks (an `assert`-based self-check or one small `test_*` file). Trivial one-liners need no test. YAGNI applies to tests too.

## Test-Driven Development (Default)

Follow RED-GREEN-REFACTOR for new features and non-trivial logic:

1. **RED**: Write a concrete failing test that defines the requirement.
2. **GREEN**: Write the minimum code to make it pass.
3. **REFACTOR**: Clean up via `/simplify` and `/code-review high` while keeping tests green.

TDD applies to features and non-trivial logic in real projects. Scripts, spikes, one-off tools, config tweaks, doc edits, typo fixes, and one-line changes skip the cycle and get the minimal runnable check instead. Use judgment.

## Progression

1. **Make it work**: functioning code that passes tests.
2. **Make it right**: refactor for clarity and maintainability.
3. **Make it fast**: optimize only after profiling reveals a real bottleneck.
4. **Remember insights**: compound knowledge so the next session starts smarter.

## Comments (default to none)

The code says *what*; a comment exists only for a *why* the code cannot show. Write far fewer comments than feel natural.

- Do not write a comment that restates what the next line does, names where code came from, or explains why your change is correct. That is talk for the reviewer, not the next reader, and it is noise once the PR merges.
- Keep only: a non-obvious *why*, a constraint the code can't express, a public API docstring, and directive comments (shellcheck, eslint, noqa, pragma, shebang).
- When a comment earns its place, make it one short sentence in plain ASCII.

## Documentation Hierarchy

1. Working code: self-documenting through clear naming.
2. Tests: executable documentation; the tests are the spec.
3. README / docs: setup, architecture, API specs.
4. Comments: last resort, per the comments rule above.

## Fail Fast & Validate

- Validate aggressively at inputs and integration boundaries. Give clear, descriptive errors when something breaks.
- Actively probe edge cases, invalid inputs, and unexpected conditions.
- Before delivering, ask: "Would a staff engineer approve this?" Codex will review afterward.

## Leave It Better

- Small unfixed problems compound. Any work tolerates a few broken windows, then collapses under twenty. Leave it better than you found it, even when fixing something unrelated.
- Simplify ruthlessly. Elegance is when there's nothing left to take away. When complexity can go without losing power, drop it.
- Clean up test scripts, data files, temporary backups, and files from abandoned strategies when done. Keep project organization consistent.
