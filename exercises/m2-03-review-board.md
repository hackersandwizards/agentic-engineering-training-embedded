# Focused review board

Duration: 25 minutes

## Outcome

The feature diff receives independent reviews with explicit evidence and
non-overlapping concerns.

## Task

Choose two or three review roles that match the diff:

- Requirements reviewer: maps changed behavior to acceptance criteria and
  safety requirements, then identifies missing evidence.
- Protocol reviewer: checks framing, ranges, endianness, correlation, timeout
  and compatibility against the protocol source.
- Verification reviewer: checks whether tests can fail for the claimed reason,
  cover negative cases and exercise the intended layer.
- Resource reviewer: checks bounded memory, timing, allocation and concurrency
  assumptions using repository evidence.

Give each reviewer read-only scope and one concern. Ask for findings ordered by
severity with file references. Validate every finding yourself and discard
unsupported style preferences.

## Done when

- Each reviewer has a distinct question and named evidence source.
- Accepted findings are fixed and reverified, or recorded with an owner.
- Human reviewers retain the approval decision.
