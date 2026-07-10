# C-100 safety requirements

The safety MCU owns these requirements. The application processor is untrusted
from the MCU's point of view. Every change to `src/mcu/` must identify the
requirements it affects and preserve their verification evidence.

## Requirements

### SR-001: Lid guard

While the lid is open, motor speed shall not exceed 500 RPM. Speeds above
6,400 RPM additionally require a locked lid. Both limits apply continuously,
not only when the command is received.

### SR-002: Spill guard

While the measured bowl temperature exceeds 60 °C, motor speed shall not
exceed 6,400 RPM on any drive path, including pulse operation. The limit
applies continuously.

### SR-003: Overtemperature cutoff

At a measured bowl temperature of 165 °C or above, the MCU shall switch off
the heater and raise an overtemperature fault. This cutoff is above the maximum
user setpoint of 160 °C.

### SR-004: Stall protection

On motor stall detection, the MCU shall de-energize the drive and raise a
motor-stall fault. Recovery requires an explicit motor-stop command.

### SR-005: Link supervision

If no valid request arrives from the application processor for five seconds
while the heater or motor is active, the MCU shall stop both outputs and raise
a link-lost fault. A new request alone does not restart an output.

### SR-006: Application liveness

The application processor feeds a 500 ms watchdog. Every long-running
operation shall continue to feed it. A watchdog reset during cooking is a
safety event.

### SR-007: Temperature sensor failure

If the bowl temperature cannot be read, the MCU shall stop active outputs and
raise a sensor-failure fault. The fault can be cleared only after a valid
sensor reading is available and an explicit motor-stop command is received.

### SR-008: Safe lid unlock

The MCU shall reject a lid-unlock request while measured motor speed is 100 RPM
or higher. A rejected request shall leave the lid locked.

## Fault handling

Entering any fault stops the motor, disables the heater controller and writes
zero heater power. `HEATER_OFF` never clears an unrelated fault. `MOTOR_STOP`
is the explicit acknowledgement command and clears a recoverable fault only
when its recovery condition is satisfied.

## Traceability

| Requirement | Main implementation | Verification |
| --- | --- | --- |
| SR-001 | `src/mcu/interlocks.cpp`, continuous motor cap | `McuLink.LidOpeningWhileRunningCutsSpeed` |
| SR-002 | `src/mcu/interlocks.cpp`, continuous motor cap | `McuLink.BurstIsRejectedForAHotBowl`, `McuLink.HotBowlContinuouslyCapsARunningMotor` |
| SR-003 | `src/mcu/interlocks.cpp`, `SafetyMcu` | `McuLink.OvertempTripsTheHeaterFault` |
| SR-004 | `src/mcu/interlocks.cpp`, `SafetyMcu` | `MotorModel.StallsOnThickDoughAtHighSpeed`, `McuLink.HeaterOffDoesNotClearAMotorFault` |
| SR-005 | `src/mcu/safety_mcu.cpp` | `McuLink.LinkLossStopsActiveOutputs` |
| SR-006 | `CookingController::tick_10ms` | `Cooking.OtaVerificationKeepsTheWatchdogFed` |
| SR-007 | `src/mcu/safety_mcu.cpp` | `McuLink.TemperatureSensorFailureStopsActiveOutputs` |
| SR-008 | `src/mcu/command_handler.cpp` | `McuLink.RefusesToUnlockWhileMotorIsMoving` |
