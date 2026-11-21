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
