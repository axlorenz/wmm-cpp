#include "coordinate_transformations.hpp"
#include "wgs84.hpp"

#include <cmath>

wmm::EcefCoordinates wmm::geodeticToEcef(const GeodeticCoordinates& geodetic)
{

    const double lat_rad = geodetic.lat_deg * deg_to_rad;
    const double lon_rad = geodetic.lon_deg * deg_to_rad;

    const double N = wgs84::a_m / std::sqrt(1 - wgs84::e_squared * square(std::sin(lat_rad)));

    const double x_m = (N + geodetic.height_ell_m) * std::cos(lat_rad) * std::cos(lon_rad);

    const double y_m = (N + geodetic.height_ell_m) * std::cos(lat_rad) * std::sin(lon_rad);

    const double z_m = ((N * (1.0 - wgs84::e_squared)) + geodetic.height_ell_m) * std::sin(lat_rad);

    return EcefCoordinates{x_m, y_m, z_m};
}
