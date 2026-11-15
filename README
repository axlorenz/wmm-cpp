# wmm-cpp

A lightweight, portable C++20 library for computing the Earth's magnetic field using the **World Magnetic Model (WMM2025)**.

> **Status:** Early development. The WMM evaluation algorithm is not yet implemented.

## Features

Planned features:

- World Magnetic Model 2025 (WMM2025)
- Geodetic coordinates based on WGS84
- Magnetic field components in the local North-East-Down (NED) coordinate system
- Magnetic field output in Tesla
- Support for decimal-year dates
- No external runtime dependencies
- Static library for Linux and Windows
- Numerical validation against official WMM reference data

## Requirements

- C++20-compatible compiler
- CMake 3.20 or newer

Supported build environments:

- Linux: GCC or Clang
- Windows: MSVC

## Build

```bash
cmake -S . -B build
cmake --build build
```

Run the example:

```bash
./build/wmm_cli
```

The CLI currently prints a placeholder message.

## Planned API

The magnetic field will be represented as:

```cpp
namespace wmm {

struct MagneticFieldNed
{
    double north_t;
    double east_t;
    double down_t;
};

}
```

All components are expressed in **Tesla**.

The coordinate system is right-handed:

- `north_t`: positive toward geographic north
- `east_t`: positive toward geographic east
- `down_t`: positive downward

Inputs will use geodetic latitude and longitude in degrees, ellipsoidal height in meters relative to WGS84, and time expressed as a decimal year.

## Model

The library will use the official WMM2025 coefficients published by NOAA/NCEI and the British Geological Survey (BGS).

- Model epoch: 2025.0
- Maximum spherical harmonic degree: 12
- Temporal validity: 2025.0 to 2030.0 (2030.0 excluded)

The library will implement the WMM evaluation algorithm independently. Official model coefficients will be used without modification.

## Limitations

The WMM describes the Earth's large-scale main magnetic field. It does not model local magnetic disturbances caused by nearby ferromagnetic objects, electrical equipment, or vehicles.

Model accuracy and numerical implementation accuracy are different concepts.

Magnetometer calibration and sensor fusion are outside the scope of this library.

## References

- NOAA/NCEI: World Magnetic Model — https://www.ncei.noaa.gov/products/world-magnetic-model
- NOAA/NCEI: WMM2025 Technical Report — https://doi.org/10.25923/prbc-s094

## License

The original C++ source code is licensed under the MIT License. See `LICENSE`.

Official WMM coefficients and reference materials are subject to their respective distribution and attribution conditions.