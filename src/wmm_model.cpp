#include "wmm_model.hpp"

#include <fstream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <format>
#include <charconv>


namespace wmm {


namespace {

    class ParseError : public std::runtime_error
    {
        public:
        using std::runtime_error::runtime_error;
    };

    class RangeError : public std::runtime_error
    {
        public:
        using std::runtime_error::runtime_error;
    };

    template<typename T>
    T parseCoefficient(std::string_view text, T min, T max)
    {
        if (min > max)
        {
            throw std::invalid_argument("min must not exceed max");
        }

        T value{};

        auto [ptr, ec] = std::from_chars(text.data(), text.data() + text.size(), value);

        // check parse error
        if(ec != std::errc() || ptr != (text.data() + text.size()))
        {
            throw ParseError(std::format("Invalid number format: '{}'", text)); 
        }

        if(!(min <= value && value <= max))
        {
            throw RangeError(std::format("Value {} out of range [{}, {}]", value, min, max)); 
        }

        return value;
    }


}

WmmModel::WmmModel(const std::filesystem::path &coefficient_file) : mwmm_coeffs(loadCoefficients(coefficient_file))
{



}

bool WmmModel::str_matches_double(std::string_view sv, double expected) noexcept
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

    if(!std::getline(input, line))
    {
        throw ParseError("Missing WMM coefficient record.");
    }


    std::istringstream iss{line};
    std::string n, m, g, h, g_dot, h_dot, extra;


    if (!(iss >> n >> m >> g >> h >> g_dot >> h_dot))
    {
        throw ParseError("Invalid coefficient record.");
    }
 
    if (iss >> extra)
    {   
        throw ParseError("Unexpected extra field in coefficient record.");

    }   

    int n_int = parseCoefficient(n, 1, 12);
    std::uint8_t n_uint8t = static_cast<std::uint8_t>(n_int);

    coefficients[0].mdegree = static_cast<std::uint8_t>(n_int);









    return {};
}

} // namespace wmm