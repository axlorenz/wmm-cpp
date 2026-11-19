#include "wmm_model.hpp"

#include <fstream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <format>
#include <charconv>


namespace wmm {


WmmModel::WmmModel(const std::filesystem::path &coefficient_file) : mwmm_coeffs(loadCoefficients(coefficient_file))
{


}

bool WmmModel::str_matches_double(std::string_view sv, double expected)
{
    double val {};
    auto [ptr, ec] = std::from_chars(sv.data(), sv.data() + sv.size(), val);
    
    return ec==std::errc() && ptr == sv.data() + sv.size() && val == expected;
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

    // next step here use istringstream to parse header

    std::string header_fields [3] = {};
    std::size_t counter {0U};
    for(std::string& i : header_fields)
    {
        ++counter;    
        if(!(header_stream >>  i))
            throw std::runtime_error(
                std::format("Header error: missing anticipated field '{}' in line '{}'.", std::to_string(counter), line)
            );
    }

    // check header

    // 1. check mmodel_epoch using the static class function

    if (!str_matches_double(header_fields[0], mmodel_epoch))
    {
        throw std::runtime_error(
            std::format("Header field 1 '{}' is not '{:.1f}'.", header_fields[0], mmodel_epoch)
        );
    }
     

    // 2. check mmodel_name
    if (header_fields[1] != mmodel_name)
    {
        throw std::runtime_error(
            std::format("Header field 2 '{}' is not '{}'.", header_fields[1], mmodel_name)
        );
    }

    // 3. check mmodel_date, commented out, for now
    // if(header_fields[2] != mmodel_date)
    // {
    //     throw std::runtime_error(
    //         std::format("Header field 3 '{}' is not '{}'.", header_fields[2], mmodel_date)
    //     );
    // }


    // parse coefficients

    std::array<WmmCoefficients, mcoeff_count> coefficients{};

    

    return {};
}

} // namespace wmm