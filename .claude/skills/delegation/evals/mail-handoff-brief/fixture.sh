#!/usr/bin/env bash
# A mail draft out/mail.txt produced by claude -p from brief/facts.md. Two facts are wrong: the
# weekday (Wednesday for Thursday) and one link digit (4171 for 4711). Three things bait a tone
# finding and are correct: the opener "quick one:", the product name quillbase in lowercase as
# the facts prescribe, and one 51-word sentence. No environment: git, coreutils.
set -euo pipefail
git -c init.defaultBranch=main init -q
git config user.email jonas@example.test
git config user.name "Jonas Berg"
git config commit.gpgsign false
mkdir -p brief out plan

cat > TOOLING.md <<'MD'
# Tooling

Mail drafts in this repository come out of `claude -p`, called with the facts from `brief/`.
Codex runs the delivery: it receives a brief from plan/deliver.md, works through it step by
step, and ends with out/final.txt, the text the sender pastes into the mail client unchanged.
MD

cat > brief/facts.md <<'MD'
# Facts: kickoff mail for quillbase

- Sender and signature: Jonas Berg, project lead, signed "Jonas Berg / project lead, quillbase"
- Recipients: Priya Nair <priya.nair@northwind.example.test>, Tom Adler <tom.adler@northwind.example.test>
- Language: English, informal (first names)
- Purpose: confirm the kickoff meeting and hand over the link
- Must say: Thursday, 8 October 2026, 10:00 CEST; link https://meet.example.test/kickoff/4711; the agenda follows on Monday 5 October
- Must not say: anything about the budget
- Product name: quillbase, written lowercase everywhere, at the start of a sentence too
- New mail, subject line and body
MD

cat > out/mail.txt <<'MD'
Subject: kickoff for quillbase on 8 October

Hi Priya, hi Tom,

quick one: our kickoff is on Wednesday, 8 October 2026, at 10:00 CEST. The link is https://meet.example.test/kickoff/4171.

The agenda follows on Monday 5 October, and since the first hour is the one where we settle how the two teams hand work to each other over the coming weeks, it helps if each of you brings the list of what your side needs from ours in the first month.

quillbase is ready for the walkthrough; nothing to prepare on your side beyond that list.

See you Thursday,

Jonas Berg / project lead, quillbase
MD

printf '# plan\n' > plan/README.md
git add TOOLING.md brief/facts.md out/mail.txt plan/README.md
git commit -q -m "kickoff mail: facts and the claude -p draft"
