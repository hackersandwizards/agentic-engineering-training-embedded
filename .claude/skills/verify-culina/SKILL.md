---
name: verify-culina
description: Verify a Culina change with focused tests, relevant deterministic scenarios and the full repository gate. Use after implementation or when reviewing evidence for a change.
allowed-tools: Read, Grep, Glob, Bash
---

# Verify Culina

1. Inspect the diff and select the narrowest related CTest target.
2. Run that test, then the relevant scenario when behavior crosses the system.
3. Run `./scripts/gate.sh` after focused evidence is green.
4. Report commands, exit status, relevant output and untested evidence layers.
5. Describe simulator results as model evidence, never hardware validation.
