---
# T116, T101 (postures.md:243-249, 116-125): the slides miss is owned in a few words; no trainer, no handover, no process explanation reaches the client
type: regex
target: { source: file, path: reply.md }
match: not_contains
flags: i
---
\bintern(e|en|er|es)?\b|Übergabe|Hand-?over|Hand-?off|festgestellt|Prozess|Trainer
