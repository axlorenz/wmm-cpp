#pragma once

#include <numbers>

namespace wmm
{

template <typename T> constexpr T square(T value)
{
    return value * value;
}

inline constexpr double deg_to_rad = std::numbers::pi_v<double> / 180.0;
inline constexpr double rad_to_deg = 180.0 / std::numbers::pi_v<double>;

struct GeodeticCoordinates
{
    double lat_deg{};
    double lon_deg{};
    double height_ell_m{};
};

struct EcefCoordinates
{
    double X_m{};
    double Y_m{};
    double Z_m{};
};

[[nodiscard]] EcefCoordinates geodeticToEcef(const GeodeticCoordinates& geodetic);

} // namespace wmm
