# C1-Link Protocol Specification

Version 1.0. Framed binary protocol between the C-100 application processor
and the safety/motor MCU over UART (in simulation: in-memory queues or a
Unix domain socket).

## Frame Layout

| Offset | Size | Field                                                  |
| ------ | ---- | ------------------------------------------------------ |
| 0      | 2    | Sync bytes `0xA5 0x5A`                                  |
| 2      | 1    | Version (high nibble, currently 1) \| flags (low nibble) |
| 3      | 1    | Frame type                                              |
| 4      | 1    | Sequence number                                         |
| 5      | 1    | Message ID                                              |
| 6      | 2    | Payload length N, little-endian, **0 ≤ N ≤ 250**        |
| 8      | N    | Payload — all multi-byte fields little-endian           |
| 8+N    | 2    | CRC16-CCITT (poly 0x1021, init 0xFFFF), little-endian   |

The CRC covers **bytes 2 through 8+N-1**: version, type, sequence, message
ID, length, and payload. Corruption anywhere behind the sync bytes must be
detectable.

Receivers shall validate the length field **before** buffering payload
bytes; a frame announcing more than 250 bytes is invalid at the moment the
length arrives, and hunting for the next sync must resume immediately.

## Frame Types

| Value | Type      | Direction  | Notes                                |
| ----- | --------- | ---------- | ------------------------------------ |
| 0x01  | Request   | app → MCU  | Sequence chosen by the app           |
| 0x02  | Response  | MCU → app  | Echoes request sequence + message ID |
| 0x03  | Telemetry | MCU → app  | Async, own sequence counter          |
| 0x04  | NACK      | MCU → app  | Request refused or malformed         |

Requesters shall correlate responses by **message ID and sequence number**
together; after a retry, a stale response to the earlier attempt carries
the old sequence and must be discarded.

A requester should allow 50 ms for a response, retry once, and treat a
second miss as a link fault.

## Message Catalog

| ID   | Name            | Request payload            | Response payload |
| ---- | --------------- | -------------------------- | ---------------- |
| 0x01 | PING            | —                          | —                |
| 0x02 | GET_VERSION     | —                          | `major u8, minor u8, patch u8` |
| 0x10 | MOTOR_SET_TARGET| `rpm u16, ramp u8`         | `granted_rpm u16` |
| 0x11 | MOTOR_STOP      | —                          | —                |
| 0x20 | HEATER_SET_TARGET | `deci_celsius i16` (370…1600) | —          |
| 0x21 | HEATER_OFF      | —                          | —                |
| 0x30 | SCALE_TARE      | —                          | —                |
| 0x31 | SCALE_READ      | —                          | `grams i32`      |
| 0x40 | LID_LOCK        | —                          | `locked u8`      |
| 0x41 | LID_UNLOCK      | —                          | —                |
| 0x80 | TELEMETRY       | `tick u32, deci_celsius i16, rpm u16, grams i32, flags u8` (13 bytes, MCU → app at 100 Hz) | |
| 0x81 | FAULT           | `code u8` (MCU → app, async) | |

Ramp profiles for `MOTOR_SET_TARGET`: 0 gentle, 1 normal, 2 fast, 3 burst
(lid must be locked; short pulse operation).

Telemetry flags: bit0 lid closed, bit1 lid locked, bit2 heater on, bit3
motor stalled.

Fault codes: 1 overtemperature, 2 motor stall, 3 sensor failure.

## Versioning

The wire format never changes shape within a major version. Any change to
frame layout or field encoding bumps the version nibble, and both sides
reject frames from a different major version.
