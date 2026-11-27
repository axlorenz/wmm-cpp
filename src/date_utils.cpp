#include "date_utils.hpp"

#include <format>
#include <stdexcept>

double wmm::toDecimalYear(const std::chrono::year_month_day& date)
{

    if (!date.ok())
    {
        throw std::invalid_argument{std::format("Date {} is invalid.", date)};
    }
    const std::chrono::year year = date.year();

    const std::chrono::sys_days start_of_year =
        std::chrono::sys_days{year / std::chrono::January / 1};

    const std::chrono::sys_days current_day = std::chrono::sys_days{date};

    const auto passed_days = (current_day - start_of_year).count();

    const double number_of_total_days = year.is_leap() ? 366.0 : 365.0;

    const double decimal_year = static_cast<int>(year) + (passed_days / number_of_total_days);

    return decimal_year;
}
