# Group feature implementation

Duration: 90 minutes

## Outcome

The group ships a bounded vertical feature from a green baseline using the
approved research and plan.

## Working loop

1. Start a fresh agent context with the reviewed research, plan and acceptance
   criteria.
2. Add or adjust a focused test before implementation when the repository can
   express the behavior deterministically.
3. Implement in small steps. Keep unrelated cleanup out of the diff.
4. Run focused verification after each meaningful step.
5. Review the final diff against the plan, then run the repository gate.
6. Save concise evidence for the closing discussion: requirement, changed flow,
   test output and remaining hardware or integration validation.

Use a real feature from the assigned team repository whenever possible.

## Culina fallback features

### A: Keep warm after manual cooking

After a manual cook completes, optionally hold 60 °C at zero motor speed until
the user stops the session. Define how the user opts in, how status exposes the
state and how faults or communication errors stop it.

### B: Stable weight display

Add a displayed-weight estimate that remains useful during vibration. Preserve
the raw measurement, bound memory and latency, and demonstrate deterministic
behavior at rest and while mixing.

### C: Recipe portion scaling

Allow a guided recipe to run at a selected portion factor. Scale ingredient
mass, define which fields do not scale, reject unsafe or unrepresentable values
and keep original recipe data immutable.

### D: Guided recipe pause and resume

Pause an active guided recipe in a defined safe actuator state, then resume the
same step without losing its progress semantics. Define behavior for timed,
weighing and user-confirmation steps and for faults while paused.

### E: Reverse rotation

Add direction to motor control. Direction may change only below 100 RPM. Define
wire compatibility, transition behavior, telemetry and tests before changing
the protocol.

### F: Link health diagnostics

Expose request latency, timeouts and last valid exchange as bounded diagnostic
telemetry without weakening fault behavior or filling memory during long runs.

The trainer selects features according to group experience. A complete narrow
slice is better than a broad partial implementation.

## Done when

- The baseline and final repository gate are green.
- New behavior has positive and negative evidence.
- The diff matches the approved plan or records why it changed.
- Remaining hardware validation and assumptions are explicit.
