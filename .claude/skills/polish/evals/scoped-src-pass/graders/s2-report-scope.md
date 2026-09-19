---
type: llm
focus: last_message
weight: 0.5
---
# S2 (SKILL.md:14-16): the report says what the src/ scope left out rather than silently dropping it
The pass was scoped to src/. The repository also holds tests/, tools/ (a README generator and its template), scripts/export.sh, check.sh and README.md. PASS only if the report names at least one of tests/, tools/, scripts/ or check.sh as outside the scope and therefore not reviewed or swept (any wording). FAIL if the report claims the whole repository was reviewed, or says nothing about what the scope excluded.
