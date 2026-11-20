#pragma once

#include "wmm_coefficients.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <string_view>

namespace wmm
{

class WmmModel
{
  private:
    static bool str_matches_double(std::string_view sv, double expected) noexcept;

    static constexpr std::uint8_t mmaxsh_deg{12};

    static constexpr std::size_t mcoeff_count{mmaxsh_deg * (mmaxsh_deg + 3) / 2};

    static_assert(mcoeff_count == 90, "WMM2025 must contain 90 coefficients");

    std::array<WmmCoefficients, mcoeff_count> mwmm_coeffs{};

    // Expected header fields
    static constexpr double mmodel_epoch{2025.0};
    static constexpr std::string_view mmodel_name{"WMM-2025"};
    static constexpr std::string_view mmodel_date{"11/13/2024"};

  public:
    explicit WmmModel(const std::filesystem::path& coefficient_file);
    static std::array<WmmCoefficients, mcoeff_count>
    loadCoefficients(const std::filesystem::path& coefficient_file);
};

} // namespace wmm
