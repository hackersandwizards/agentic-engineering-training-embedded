# C-100 Safety Requirements

The safety MCU owns these requirements; the application processor is
untrusted from the MCU's point of view. Every change to `src/mcu/` must
state which requirement it maintains.

## Requirements

**SR-001 — Lid guard.**
While the lid is open, motor speed shall not exceed 500 RPM. Speeds above
6,400 RPM additionally require the lid to be locked. Applies continuously,
not only at command time.

**SR-002 — Spill guard.**
While the bowl temperature exceeds 60 °C, motor speed shall not exceed
6,400 RPM, on every drive path including pulse operation. Applies
continuously, not only at command time.

**SR-003 — Overtemperature cutoff.**
At a measured bowl temperature of 165 °C or above, the heater shall be
switched off and a fault raised. The cutoff sits above the maximum user
setpoint (160 °C) so it only trips on genuine runaway.

**SR-004 — Stall protection.**
On motor stall detection, the drive shall be de-energized and a fault
raised. Recovery requires an explicit stop command.

**SR-005 — Link supervision.**
If no valid frame arrives from the application processor for 5 seconds
while the heater or motor is active, the MCU shall bring both to a safe
state (heater off, motor stopped) and raise a fault.

**SR-006 — Liveness.**
The application processor feeds a 500 ms watchdog. Every long-running
operation must keep feeding it; a watchdog reset during cooking is a
safety event, not a nuisance.

## Traceability

| Requirement | Implementation                                | Verification                     |
| ----------- | --------------------------------------------- | -------------------------------- |
| SR-001      | `src/mcu/interlocks.cpp`, continuous cap      | `McuLink.LidOpeningWhileRunningCutsSpeed` |
| SR-002      | `src/mcu/interlocks.cpp`                      | `McuLink.ClampsSpeedWithUnlockedLid` |
| SR-003      | `src/mcu/interlocks.cpp`, `SafetyMcu`         | `McuLink.OvertempTripsTheHeaterFault` |
| SR-004      | `src/mcu/interlocks.cpp`, `MotorModel` stall  | `MotorModel.StallsOnThickDoughAtHighSpeed` |
| SR-005      | `src/mcu/safety_mcu.cpp`                      | —                                |
| SR-006      | `CookingController::tick_10ms`                | `Cooking.ManualModeBoilsWaterAndShutsDown` |
