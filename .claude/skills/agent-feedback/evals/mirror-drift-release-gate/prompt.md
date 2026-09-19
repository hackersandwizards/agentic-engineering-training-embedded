---
runs: 3
max_turns: 40
timeout_seconds: 900
allowed_tools: [Read, Glob, Grep, Bash, Write, Edit, Skill]
---
The deploy skill let a release run in the alpha checkout tag v1.4.0 while the pipeline on main was red. What I told the run is in transcript.md. Our agent config lives in ./hub and goes out to the checkouts under ./repos with hub/scripts/sync-agent-config.sh. Fix the skill so a release waits for a green pipeline on main, get it out to the checkouts, and commit. Nobody answers questions in this session.
