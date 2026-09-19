---
# G13: a clear bug report is fixed without a clarifying question
type: llm
focus: last_message
weight: 0.5
---
PASS if the report states the fix was made and the test added. FAIL if the response instead asks the user which fix they want, whether to raise or tolerate the comma, or otherwise stops before changing code.
