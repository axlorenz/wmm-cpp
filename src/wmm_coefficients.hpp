#pragma once

#include <cstdint>


namespace wmm {

    struct WmmCoefficients{
        std::uint8_t mdegree {0};
        std::uint8_t morder {0};
        double mg_nt {0.0};
        double mh_nt {0.0};
        double mg_dot_nt_y {0.0};
        double mh_dot_nt_y {0.0};
    };

}