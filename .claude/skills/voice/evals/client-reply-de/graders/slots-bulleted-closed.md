---
type: llm
focus: { source: file, path: reply.md }
---
# T108 (postures.md:147, 152): slots are hyphen bullets and the slot passage closes on a short question
Look only at the passage that offers the two make-up slots (6 October and 8 October). Each slot stands on its own line starting with `- `. Right after the slots, with at most one sentence about the Wednesday constraint in between, comes a question of at most four words that hands the pick to her, such as `Was ist dir lieber?` or `Was passt euch besser?`. What the mail says later, about the mobile team or in its closing line, is outside this passage and does not count.
FAIL if a slot is not on its own `- ` line, or if no such question follows the slots. Otherwise PASS.
