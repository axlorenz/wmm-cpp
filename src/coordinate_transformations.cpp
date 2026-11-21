#include "coordinate_transformations.hpp"
#include "wgs84.hpp"

#include <cmath>

wmm::EcefCoordinates wmm::geodeticToEcef(const GeodeticCoordinates& geodetic)
{

    const double N_ = wgs84::a / std::sqrt(1 - wgs84::e_squared *
                                                   square(std::sin(geodetic.lon_deg * deg_to_rad)));

    // Todo add computation of X,Y,Z
    return EcefCoordinates();
}
