# C1-Link protocol specification

Version 1.0. C1-Link is the framed binary protocol between the C-100
application processor and safety MCU. The host simulation uses in-memory
queues or a Unix domain socket in place of UART.

## Frame layout

| Offset | Size | Field |
| --- | --- | --- |
| 0 | 2 | Sync bytes `0xA5 0x5A` |
| 2 | 1 | Version in high nibble, flags in low nibble |
| 3 | 1 | Frame type |
| 4 | 1 | Sequence number |
| 5 | 1 | Message ID |
| 6 | 2 | Payload length N, little-endian, `0 <= N <= 250` |
| 8 | N | Payload with little-endian multi-byte fields |
| 8+N | 2 | CRC16-CCITT, polynomial `0x1021`, initial value `0xFFFF` |

The CRC covers bytes 2 through `8+N-1`: version, type, sequence, message ID,
length and payload. Receivers validate the length before buffering payload
bytes. A length above 250 is invalid as soon as the length field arrives, and
the parser immediately resumes its search for sync bytes.

## Frame types

| Value | Type | Direction | Behavior |
| --- | --- | --- | --- |
| `0x01` | Request | app to MCU | Sequence selected by the app |
| `0x02` | Response | MCU to app | Echoes request sequence and message ID |
| `0x03` | Telemetry | MCU to app | Asynchronous, independent sequence |
| `0x04` | NACK | MCU to app | Request refused or malformed |

Requesters correlate responses by message ID and sequence together. A response
with a stale sequence is ignored. The application allows 50 ms for a response;
a missing response produces a timeout status. A NACK produces a protocol-error
status. Either status is surfaced to the active cooking controller.

While an output is active, the application sends an untracked `PING` at least
once per second. The MCU enters its link-lost safe state after five seconds
without a valid request.

## Message catalog

| ID | Name | Request payload | Response payload |
| --- | --- | --- | --- |
| `0x01` | `PING` | empty | empty |
| `0x02` | `GET_VERSION` | empty | `major u8, minor u8, patch u8` |
| `0x10` | `MOTOR_SET_TARGET` | `rpm u16, ramp u8` | `granted_rpm u16` |
| `0x11` | `MOTOR_STOP` | empty | empty |
| `0x20` | `HEATER_SET_TARGET` | `deci_celsius i16` in 370 to 1600 | empty |
| `0x21` | `HEATER_OFF` | empty | empty |
| `0x30` | `SCALE_TARE` | empty | empty |
| `0x31` | `SCALE_READ` | empty | `grams i32` |
| `0x40` | `LID_LOCK` | empty | `locked u8` |
| `0x41` | `LID_UNLOCK` | empty | empty; NACK at 100 RPM or higher |
| `0x80` | `TELEMETRY` | asynchronous MCU message | `tick u32, deci_celsius i16, rpm u16, grams i32, flags u8` |
| `0x81` | `FAULT` | asynchronous MCU message | `code u8` |

Motor ramp profiles are `0` gentle, `1` normal, `2` fast and `3` burst.
Burst requires a locked lid and a bowl temperature at or below 60 °C. Tare is
rejected while measured motor speed exceeds 50 RPM.

Telemetry flags are bit 0 lid closed, bit 1 lid locked, bit 2 heater on and bit
3 motor stalled.

Fault codes are `1` overtemperature, `2` motor stall, `3` sensor failure and
`4` link lost.

## Versioning

The wire format does not change shape within a major version. A change to frame
layout or field encoding increments the version nibble. Both sides reject
frames from a different major version.
