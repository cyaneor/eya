/**
 * @file date_year.h
 * @brief Year handling utilities for calendar operations
 *
 * @details This header provides types and functions for working with calendar years.
 *          It includes year validation and leap year calculation
 *          functionality based on the Gregorian calendar system.
 *
 * The module defines:
 * - Year type (eya_date_year_t) as an unsigned short
 * - Minimum and maximum valid year values
 * - Year validation function
 * - Leap year detection function
 *
 * @note All functions in this module use the Gregorian calendar rules
 *       and assume year values are within the unsigned short range.
 */

#ifndef EYA_DATE_YEAR_H
#define EYA_DATE_YEAR_H

#include "bool.h"
#include "numeric.h"
#include "attribute.h"

#ifndef EYA_DATE_YEAR_T_MIN
/**
 * @def EYA_DATE_YEAR_T_MIN
 * @brief Minimum valid value for a year (minimum unsigned short value)
 * @details Represents the smallest valid year value that can be represented
 *          by the eya_date_year_t type.
 */
#    define EYA_DATE_YEAR_T_MIN EYA_USHORT_T_MIN
#endif // EYA_DATE_YEAR_T_MIN

#ifndef EYA_DATE_YEAR_T_MAX
/**
 * @def EYA_DATE_YEAR_T_MAX
 * @brief Maximum valid value for a year (maximum unsigned short value)
 * @details Represents the largest valid year value that can be represented
 *          by the eya_date_year_t type.
 */
#    define EYA_DATE_YEAR_T_MAX EYA_USHORT_T_MAX
#endif // EYA_DATE_YEAR_T_MAX

/**
 * @typedef eya_date_year_t
 * @brief Type representing a calendar year
 * @details This type is an alias for eya_ushort_t and represents years
 *          in the range [EYA_DATE_YEAR_T_MIN, EYA_DATE_YEAR_T_MAX].
 *          It is used to store and manipulate year values in date operations.
 */
typedef eya_ushort_t eya_date_year_t;

EYA_COMPILER(EXTERN_C_BEGIN)

/**
 * @brief Validates if a year value is within the acceptable range
 * @param[in] self The year value to validate
 * @return true if the year is within range,
 *         false otherwise
 *
 * @details This function checks if the provided year value falls
 *          within the defined valid range for the `eya_date_year_t` type.
 *
 * Example usage:
 * @code
 * if (eya_date_year_is_valid(2024)) {
 *     // Year is valid
 * }
 * @endcode
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_date_year_is_valid(eya_date_year_t self);

/**
 * @brief Checks if a given year is a leap year
 * @param[in] self The year to check for leap year status
 * @return true if the year is a leap year, false otherwise
 * @details A leap year is divisible by 4, but not by 100 unless also divisible by 400.
 *          This function implements the Gregorian calendar leap year rules.
 *
 * @note The function assumes the Gregorian calendar system.
 *
 * Example usage:
 * @code
 * if (eya_date_year_is_leap(2024)) {
 *     // 2024 is a leap year
 * }
 * @endcode
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_date_year_is_leap(eya_date_year_t self);

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_DATE_YEAR_H