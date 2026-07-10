# Culina C-100 Firmware

Firmware for the Culina C-100 smart kitchen machine: an application processor and a
safety/motor MCU talking over the C1-Link serial protocol. The entire device — motor,
heater, scale, lid — is simulated on the host, so the firmware builds and runs anywhere
with CMake and a C++17 compiler. It serves as a realistic playground for agentic
engineering exercises.

## Quick Start

```sh
cmake --preset dev
cmake --build --preset dev
ctest --preset dev
```

More sections (architecture, simulator usage, protocol reference) will land as the
firmware grows.

## License

For training purposes. See [LICENSE](LICENSE).
