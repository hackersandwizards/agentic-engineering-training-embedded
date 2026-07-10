# MX400 reluctance motor drive data

Revision 2.4. Integration data for the C-100 main drive.

## Electrical characteristics

| Parameter            | Min | Typ    | Max    | Unit |
| -------------------- | --- | ------ | ------ | ---- |
| Supply voltage       | 210 | 230    | 250    | V AC |
| Continuous power     |     | 500    | 620    | W    |
| Speed range          | 100 |        | 10,700 | RPM  |
| Idle current         |     | 150    | 220    | mA   |
| Stall trip current   |     | 2,400  | 2,600  | mA   |

## Speed ramp limits

Commanded acceleration must stay inside the drive's derating envelope.
Exceeding these rates overloads the rotor bearings and voids the drive
warranty.

| Operating region     | Max acceleration | Max deceleration |
| -------------------- | ---------------- | ---------------- |
| 0 to 8,000 RPM       | 3,500 RPM/s      | 14,000 RPM/s     |
| 8,000 to 10,700 RPM  | 2,500 RPM/s      | 14,000 RPM/s     |

Short chopping bursts (≤ 2 s) may command the maximum speed step directly;
the drive's internal limiter then applies the envelope above.

## Duty command

The drive accepts a normalized duty command in [0.0, 1.0] mapping linearly
to the speed range. Reverse rotation is selected via a separate direction
input and must only change below 100 RPM.

## Thermal derating

Above 70 °C drive-housing temperature, continuous power derates linearly to
350 W at 95 °C. The housing sensor is exposed as the drive's current
telemetry; sustained operation above 2,000 mA indicates derating territory.
