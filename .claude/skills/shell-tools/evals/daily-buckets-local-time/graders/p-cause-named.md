---
# P (prompt): the final message names UTC or the time zone as the cause
type: regex
pattern: 'UTC|time ?zone|Zeitzone|local time'
flags: i
target: last_message
match: contains
weight: 0.5
---
