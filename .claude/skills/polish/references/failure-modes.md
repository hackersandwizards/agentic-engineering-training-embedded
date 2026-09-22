# Failure modes

Defects a competent review misses by default. What every reviewer already checks (dead code,
shallow modules, injection, N+1, secrets) needs no entry here.

Report at most 5 to 8 findings, merged by root cause. Each one names **the check that proves the fix
worked**, and **the most plausible innocent explanation** (local convention, a constraint you cannot
see, work in progress). If the innocent reading holds, drop the finding.

Before reporting two passages as contradictory, name the object each one governs in one word. Where
the two words differ there is no finding. A finding whose stated basis has been refuted is
finished, never re-argued on a fresh objection.

## Comments

- Deletion is the default. Delete, rather than shorten, a comment that restates the code, names
  where it came from, or argues that a change is correct.
- Keep a non-obvious why or a constraint the code cannot express: one sentence, in the file's
  prevailing style, never two styles for the same kind of declaration.
- Sweep `#`, `<!-- -->` and `/* */` as well as `//`, and the banner blocks that label the section
  below them.
- Keep public API docstrings, license headers, and directive comments (shellcheck, eslint, noqa,
  pragma, shebang).

## Instruction prose that justifies instead of instructing

Measure a section against what an agent does with it: an instruction is written for a literal
reader, and a rule's history is not part of the rule.

- Consequence narration where naming the obligation would do. Keep one why-clause only where it
  stops an agent skipping the step.
- One observation written as a law ("on every response"). Scope it to what was seen, or verify it.
- Procedure a capable model runs unprompted: numbered steps in the obvious order, tool names in
  sequence, a mode list over verbs the tool schema already names, a default restated as a rule.
- A branch, flag or mode whose other arm nobody takes, and a per-person or per-machine exception
  where one default with the person read off the session would do.

What stays is what the model gets wrong without the line: a measured number, a verbatim phrasing,
a silent failure, a file convention. List the skill's traps first and re-read each cut against
that list.

Cutting is a check deletion when the sentence carried the only "stop and ask" on a path.

## Silently inert code

Reads as correct, passes every gate, and never fires.

- A selector or condition that cannot match. Scoped CSS against slotted content is the canonical case:
  the child carries the caller's scope, so the rule needs `:global` or it matches nothing.
- A branch no caller reaches, a flag written and never read, a field populated and never rendered.

Found by running the thing, not reading it. A green gate is not evidence that a visible change works.

## Weakened verification

Diff the test files for a check weakened to make it pass: a production branch keyed on a fixture
name, a test mirroring the implementation method-for-method, or one asserting only that a mock was
called.

A test earns trust by failing: delete the guard it names and watch it go red. Bun caps regex
backtracking where V8 does not, so a production hang can measure as merely slow under vitest. Code
that drops or rewrites input also needs one run over the real corpus, diffed against the unfiltered
output.

## A gate that ran but was never read

- Piping it (`check | tail -4 && commit`) makes the pipeline exit status the *last* command's,
  so an `&&` chain proceeds over a red gate. Run the gate on its own line and read its exit code.
- A commit whose paths the pre-commit hook does not route runs no gate at all. Check what the
  hook matches before trusting it to catch you.
- `git diff --cached --name-only` reports a rename by its new path alone, so a check scoped to
  that list never sees the path that went away. A hook building a scope from it needs
  `--no-renames`.
- When a gate is red, establish whose change made it red before acting, from `git status` and
  `git diff` alone. In a shared working tree the failure is often another session's in-flight
  file, and neither stashing it, reverting it nor bypassing the gate is yours to do.

## Fabricated dependencies

Confirm every new helper, import, or package exists and is the canonical one here. A plausible name
that resolves to nothing survives review easily and fails at runtime.

## Reported coverage

A claim about how much was checked, that cannot be substantiated: a count that does not match the
collection size, or a verification asserted without being run.

## Local idiom

Read the handwritten code next to the change before judging its style. Local consistency is evidence;
do not impose a convention that fights the surrounding file.

Evidence of a convention is not evidence of a spec. One file differing from thirty siblings is an
inconsistency; calling it broken needs the spec, fetched. Normalise it as consistency, or check
first and report what the check said.
