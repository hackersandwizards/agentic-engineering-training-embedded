---
runs: 3
max_turns: 40
timeout_seconds: 1200
allowed_tools: [Read, Glob, Grep, Bash, Write, Edit, Skill]
---
Ops says `reports/daily.tsv` is wrong for the first week of June: June 5 is missing and June 2 is short. The report comes from `scripts/daily-counts.sh` over `data/events.jsonl`. Find the cause, fix the script, regenerate the report, and commit both. Name the cause in your final message.
