#pragma once

namespace wgs84
{
inline constexpr double a_m = 6378137.0;
inline constexpr double f = 1 / 298.257223563;
inline constexpr double b_m = a_m * (1 - f);
inline constexpr double e_squared = f * (2.0 - f);
inline constexpr double e_prime_squared = e_squared / (1.0 - e_squared);

} // namespace wgs84
