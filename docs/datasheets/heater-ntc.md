# Bowl-base NTC probe data

Revision 1.1. Temperature sensing for the C-100 heating plate.

## Characteristics

| Parameter               | Value                     |
| ----------------------- | ------------------------- |
| Nominal resistance      | 100 kΩ at 25 °C (B=4250)  |
| Measurement range       | -20 to 180 °C             |
| Accuracy                | ±0.5 °C (0 to 120 °C)     |
|                         | ±1.5 °C (120 to 180 °C)   |
| Thermal response (τ63)  | 1.8 s against the bowl    |
| Sampling recommendation | ≥ 100 Hz, median-of-5     |

## Resistance table

| °C  | kΩ     |
| --- | ------ |
| 0   | 327.2  |
| 25  | 100.0  |
| 37  | 60.1   |
| 60  | 24.9   |
| 100 | 6.71   |
| 160 | 1.29   |

## Integration notes

The probe reads the plate, not the food: during fast heating the bowl
contents lag by several degrees (see τ63). Control loops holding tight
temperature bands should average multiple readings rather than act on
single samples.
