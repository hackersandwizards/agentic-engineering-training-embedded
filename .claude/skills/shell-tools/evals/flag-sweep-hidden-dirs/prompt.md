---
runs: 3
max_turns: 40
timeout_seconds: 1200
allowed_tools: [Read, Glob, Grep, Bash, Write, Edit, Skill]
---
acmectl 1.4 dropped the `--legacy-auth` flag: auth is detected from the profile now, and the flag makes the CLI exit 2. Remove every use of it from this repository. Add `scripts/check-flags.sh` for CI: it exits 1 when `--legacy-auth` appears anywhere in the repository and 0 otherwise. Commit. Then write `SWEEP.md` with the exact command you ran to prove that no reference remains, and its output.
