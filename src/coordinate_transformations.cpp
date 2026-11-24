#include "coordinate_transformations.hpp"
#include "wgs84.hpp"

#include <cmath>
#include <stdexcept>

namespace
{
double compute_prime_vertical_radius(const double lat_rad)
{

    return wgs84::a_m / std::sqrt(1.0 - wgs84::e_squared * wmm::square(std::sin(lat_rad)));
}
} // namespace

wmm::EcefCoordinates wmm::geodeticToEcef(const GeodeticCoordinates& geodetic)
{

    const double lat_rad = geodetic.lat_deg * deg_to_rad;
    const double lon_rad = geodetic.lon_deg * deg_to_rad;

    const double N_lat = compute_prime_vertical_radius(lat_rad);

    const double x_m = (N_lat + geodetic.height_ell_m) * std::cos(lat_rad) * std::cos(lon_rad);

    const double y_m = (N_lat + geodetic.height_ell_m) * std::cos(lat_rad) * std::sin(lon_rad);

    const double z_m =
        ((N_lat * (1.0 - wgs84::e_squared)) + geodetic.height_ell_m) * std::sin(lat_rad);

    return EcefCoordinates{x_m, y_m, z_m};
}

wmm::GeodeticCoordinates wmm::ecefToGeodetic(const EcefCoordinates& ecef)
{
    constexpr double pole_threshold_m = 1e-6;
    constexpr double epsilon_rad = 1e-12;
    constexpr int max_iterations = 10;

    const double p_ = std::sqrt(square(ecef.X_m) + square(ecef.Y_m));
    if (p_ == 0.0 && ecef.Z_m == 0.0)
    {
        throw std::domain_error("Geodetic coordinates undefined at Earth's center");
    }

    if (p_ < pole_threshold_m)
    {
        const double latitude_deg = std::copysign(90.0, ecef.Z_m);
        const double longitude_deg = 0.0;
        const double height_ell_m = std::abs(ecef.Z_m) - wgs84::b_m;

        return GeodeticCoordinates{latitude_deg, longitude_deg, height_ell_m};
    }

    const double beta_ = std::atan2(ecef.Z_m * wgs84::a_m, p_ * wgs84::b_m);

    const double cubed_sin_beta = cubed(std::sin(beta_));
    const double cubed_cos_beta = cubed(std::cos(beta_));

    const double phi_start_atan2_first_arg =
        ecef.Z_m + wgs84::e_prime_squared * wgs84::b_m * cubed_sin_beta;
    const double phi_start_atan2_2nd_arg = p_ - wgs84::e_squared * wgs84::a_m * cubed_cos_beta;

    const double phi_start = std::atan2(phi_start_atan2_first_arg, phi_start_atan2_2nd_arg);

    double N_k{}, phi_k{phi_start}, phi_kplus1{};

    for (unsigned int i = 0; i < max_iterations; ++i)
    {
        N_k = compute_prime_vertical_radius(phi_k);
        phi_kplus1 = std::atan2(ecef.Z_m + wgs84::e_squared * N_k * std::sin(phi_k), p_);

        if (std::abs(phi_kplus1 - phi_k) < epsilon_rad)
        {
            break;
        }

        phi_k = phi_kplus1;
    }

    const double lat_deg = phi_kplus1 * rad_to_deg;
    const double lon_deg = std::atan2(ecef.Y_m, ecef.X_m) * rad_to_deg;
    const double N_final = compute_prime_vertical_radius(phi_kplus1);
    const double h_ell = p_ / std::cos(phi_kplus1) - N_final;

    return GeodeticCoordinates{lat_deg, lon_deg, h_ell};
}

wmm::SphericalCoordinates wmm::geodeticToSpherical(const GeodeticCoordinates& geodetic)
{
    const double lat_rad = geodetic.lat_deg * deg_to_rad;
    const double lon_rad = geodetic.lon_deg * deg_to_rad;
    const double height_ell_m = geodetic.height_ell_m;

    const double N_lat = compute_prime_vertical_radius(lat_rad);

    const double p_ = (N_lat + height_ell_m) * std::cos(lat_rad);

    const double z_ = (N_lat * (1.0 - wgs84::e_squared) + height_ell_m) * std::sin(lat_rad);

    const double radius_m = std::hypot(p_, z_);
    const double colatitude_rad = std::atan2(p_, z_);

    return SphericalCoordinates{radius_m, colatitude_rad, lon_rad};
}
