#pragma once

namespace wgs84
{
inline constexpr double a = 6378137.0;
inline constexpr double f = 1 / 298.257223563;
inline constexpr double e_squared = f * (2.0 - f);

} // namespace wgs84
