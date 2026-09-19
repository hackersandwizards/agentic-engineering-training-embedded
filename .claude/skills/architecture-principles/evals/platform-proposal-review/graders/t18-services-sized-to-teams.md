---
# T18 (SKILL.md:21,40): services are sized to team capacity and every new one is debt until proven, so the review rejects 14 services for two teams of four
type: llm
focus: { source: file, path: docs/review-platform-2027.md }
weight: 3
---
The proposal splits the monolith into 14 independently deployable services shared by two teams of four engineers. FAIL if the review accepts that number, or proposes a count of deployables above the number of teams without a stated coordination reason, or judges the decomposition only by domain boundaries without tying the count to the two teams; PASS if it rejects 14 as too many for eight people and sizes the split to the teams (two deployables, one per team, or keeping the monolith with enforced module boundaries).
