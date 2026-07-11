# Group feature implementation

Duration: 75 minutes before lunch, 45 minutes after

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

## Feature options

### A: Keep warm after manual cooking

After a manual cook completes, optionally hold 60 °C at zero motor speed until
the user stops the session. Define how the user opts in, how status exposes the
state and how faults or communication errors stop it.

### B: Stable weight display

Add a displayed-weight estimate that remains useful during vibration. Preserve
the raw measurement, bound memory and latency, and demonstrate deterministic
behavior at rest and while mixing.

### C: Turbo pulse

Add a bounded maximum-speed burst with a hard duration limit and automatic
stop. Define the permitted duration range, the lid interlock behavior and what
happens when a second pulse is requested while one runs.

### D: Dough kneading mode

Add an interval kneading program that alternates mixing and rest phases
without heating. Define the interval pattern, its end condition and how status
distinguishes an active phase from a rest phase. Time must advance through the
simulation, not the host clock.

### E: Sous-vide mode

Hold a target temperature inside a tight band for a long duration. Define the
permitted temperature range, what counts as leaving the band and the evidence
that the band holds over simulated hours. Tests must assert the band, not just
that temperature changed.

### F: Reverse rotation

Add direction to motor control. Direction may change only below 100 RPM. Define
wire compatibility, transition behavior, telemetry and tests before changing
the protocol.

### G: Link health diagnostics

Expose request latency, timeouts and last valid exchange as bounded diagnostic
telemetry without weakening fault behavior or filling memory during long runs.

The trainer assigns features according to group experience. A complete narrow
slice is better than a broad partial implementation. A group that finishes
early hardens its feature instead of starting a second one.

## Done when

- The baseline and final repository gate are green.
- New behavior has positive and negative evidence.
- The diff matches the approved plan or records why it changed.
- Remaining hardware validation and assumptions are explicit.
