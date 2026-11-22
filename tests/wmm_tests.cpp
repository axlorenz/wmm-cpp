#include "coordinate_transformations.hpp"
#include "wmm_model.hpp"

#include <cstdint>
#include <gtest/gtest.h>

namespace
{
constexpr auto near_error = 1e-10;
const std::filesystem::path wmm_coeff_2025_path{"../data/WMM2025.COF"};
} // namespace

TEST(WmmModelTest, CoeffLoadedWithoutError)
{

    wmm::WmmModel wmm_model{wmm_coeff_2025_path};
}

TEST(WmmModelTest, CoefficientsLoadedCorrectly)
{
    const auto coeffs = wmm::WmmModel::loadCoefficients(wmm_coeff_2025_path);

    EXPECT_EQ(coeffs.at(11).mdegree, 4U);
    EXPECT_EQ(coeffs.at(16).morder, 2U);

    EXPECT_DOUBLE_EQ(coeffs.at(30).mg_nt, 59.3);
    EXPECT_DOUBLE_EQ(coeffs.at(30).mh_nt, -1.0);
    EXPECT_DOUBLE_EQ(coeffs.at(30).mg_dot_nt_y, 0.5);
    EXPECT_DOUBLE_EQ(coeffs.at(30).mh_dot_nt_y, -0.8);
}

TEST(CoordinateTransformationsTest, GeodeticToEcefAtEquator)
{
    const wmm::GeodeticCoordinates geodetic{0.0, 0.0, 0.0};

    const auto ecef = wmm::geodeticToEcef(geodetic);

    EXPECT_NEAR(ecef.X_m, 6378137.0, 1e-6);
    EXPECT_NEAR(ecef.Y_m, 0.0, 1e-6);
    EXPECT_NEAR(ecef.Z_m, 0.0, 1e-6);
}

TEST(CoordinateTransformationsTest, GeodeticToEcefAt45Degrees)
{
    const wmm::GeodeticCoordinates geodetic{45.0, 45.0, 0.0};

    const auto ecef = wmm::geodeticToEcef(geodetic);

    EXPECT_NEAR(ecef.X_m, 3194419.145, 1e-4);
    EXPECT_NEAR(ecef.Y_m, 3194419.145, 1e-4);
    EXPECT_NEAR(ecef.Z_m, 4487348.409, 1e-3);
}

TEST(CoordinateTransformationsTest, GeodeticToEcefAtNorthPole)
{
    const wmm::GeodeticCoordinates geodetic{90.0, 0.0, 0.0};

    const auto ecef = wmm::geodeticToEcef(geodetic);

    EXPECT_NEAR(ecef.X_m, 0.0, 1e-6);
    EXPECT_NEAR(ecef.Y_m, 0.0, 1e-6);
    EXPECT_NEAR(ecef.Z_m, 6356752.314245, 1e-6);
}
