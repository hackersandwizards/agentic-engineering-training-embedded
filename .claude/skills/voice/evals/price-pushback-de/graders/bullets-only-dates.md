---
# T12 (personal-voice.md:29): bullets only for groups or dates
# A bullet line or a numbered line fails when it carries any word beyond weekdays, months, `bis`, `und`, `oder`, `ab`, `von`, `Uhr`, `KW`, `Ende`, `Anfang`, `Mitte`, `Woche`. A plain `1. bis 3. Dezember` line is a date and passes. A mail with no list passes
type: regex
target: { source: file, path: reply.md }
match: not_contains
---
(^|\n)[ \t]*(?:[-*•]|\d{1,2}[.)])[ \t]+(?=[^\n]*?(?<![A-Za-zÄÖÜäöüß])(?!(?:Mo|Di|Mi|Do|Fr|Sa|So|Montag|Dienstag|Mittwoch|Donnerstag|Freitag|Samstag|Sonntag|Januar|Februar|März|April|Mai|Juni|Juli|August|September|Oktober|November|Dezember|Jan|Feb|Mär|Apr|Jun|Jul|Aug|Sep|Sept|Okt|Nov|Dez|Uhr|bis|und|oder|ab|von|KW|Ende|Anfang|Mitte|Woche)(?![A-Za-zÄÖÜäöüß]))[A-Za-zÄÖÜäöüß]{2,})
