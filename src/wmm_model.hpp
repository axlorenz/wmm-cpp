#pragma once

#include "wmm_coefficients.hpp"

#include <array>
#include <cstdint>
#include <cstddef>
#include <filesystem>

namespace wmm {

    class WmmModel{
        private:
            static constexpr std::uint8_t mmaxsh_deg {12};

            static constexpr std::size_t mcoeff_count {
                mmaxsh_deg * (mmaxsh_deg + 3) / 2
            };

            static_assert(mcoeff_count == 90,
                  "WMM2025 must contain 90 coefficients");

            std::array<WmmCoefficients, mcoeff_count> mwmm_coeffs {};
            static constexpr double mmodel_epoch {2025.0};

        public:

        explicit WmmModel(const std::filesystem::path& coefficient_file);
        static std::array<WmmCoefficients, mcoeff_count> loadCoefficients(const std::filesystem::path& coefficient_file);

    };

}