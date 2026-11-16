#include "wmm_model.hpp"

#include <fstream>
#include <stdexcept>
#include <string>
#include <sstream>

namespace wmm {

WmmModel::WmmModel(const std::filesystem::path &coefficient_file) : mwmm_coeffs(loadCoefficients(coefficient_file))
{


}

std::array<WmmCoefficients, WmmModel::mcoeff_count> WmmModel::loadCoefficients(const std::filesystem::path &coefficient_file)
{
    std::ifstream input {coefficient_file};

    if(!input.is_open())
    {
        throw std::runtime_error(
            "Can't open WMM coefficient file: " + coefficient_file.string()
        );
    }
    
    std::string line {};

    if (!std::getline(input, line)){

        throw std::runtime_error("Missing WMM coefficient file header");
    }

    std::istringstream header_stream{line};

    // next step here use istrinhgstream to parse header


    return {};
}

} // namespace wmm