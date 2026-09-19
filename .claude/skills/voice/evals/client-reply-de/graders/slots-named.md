---
type: llm
focus: { source: file, path: reply.md }
---
# T108, T23 (postures.md:153-157; personal-voice.md:145-147): both slots named with date and time, the personal reason kept
Find the passage about the make-up session for the two who missed day two. PASS only if all three hold:
1. Both slots appear with date and time: Tuesday 6 October 14 to 16 and Thursday 8 October 10 to 12, in any German date form (`Di, 6.10., 14-16 Uhr`, `Dienstag, 6. Oktober, 14 bis 16 Uhr`). FAIL on "wann passt es euch" or any open "when are you free" in place of a slot.
2. The Wednesday constraint keeps the reason the writer gave, the kids (`Kinder`, `Kids`, `die Kleinen`). FAIL if the reason is dropped or swapped for a professional one (another appointment, a client, `keine Zeit`).
3. No booking link and no "I'll send an invite" replaces the named slots.
