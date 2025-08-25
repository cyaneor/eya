#ifndef EYA_DATE_UTIL_H
#define EYA_DATE_UTIL_H

#include "interval_util.h"

/**
 * @def eya_date_is_valid_year(min, max, year)
 * @brief Checks if a year is within the specified valid range
 *
 * This macro validates that a given year falls within a closed interval [min, max].
 * The check is inclusive of both the minimum and maximum boundaries.
 *
 * @param[in] min   The minimum valid year (inclusive)
 * @param[in] max   The maximum valid year (inclusive)
 * @param[in] year  The year to validate
 *
 * @return Non-zero if the year is within the valid range, zero otherwise
 *
 * @note Uses eya_interval_closed_contains_value() internally for the range check
 * @see eya_interval_closed_contains_value
 */
#define eya_date_is_valid_year(min, max, year) eya_interval_closed_contains_value(min, max, year)

/**
 * @def eya_date_is_leap_year(year)
 * @brief Determines if a given year is a leap year
 *
 * This macro implements the standard leap year algorithm:
 * - Divisible by 4 AND
 * - Either NOT divisible by 100 OR divisible by 400
 *
 * @param[in] year The year to check (should be a valid year)
 * @return Non-zero if the year is a leap year, zero otherwise
 *
 * @note Follows the Gregorian calendar rules for leap years
 * @warning The year parameter should be validated first
 *          if working with arbitrary input
 */
#define eya_date_is_leap_year(year) (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0))

#endif // EYA_DATE_UTIL_H
