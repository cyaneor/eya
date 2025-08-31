/**
 * @file date_year.h
 * @brief Header file defining the year type and related constants for date operations
 * @details This file provides the type definition and constants
 *          for representing and manipulating calendar years.
 *
 *          It includes the minimum and maximum valid year values,
 *          as well as the type alias used for year representation.
 */

#ifndef EYA_DATE_YEAR_H
#define EYA_DATE_YEAR_H

#include "numeric.h"

#ifndef EYA_DATE_YEAR_MIN
/**
 * @def EYA_DATE_YEAR_MIN
 * @brief Minimum valid value for a year (minimum unsigned short value)
 * @details Represents the smallest valid year value that can be represented
 *          by the eya_date_year_t type.
 */
#    define EYA_DATE_YEAR_MIN EYA_USHORT_MIN
#endif // EYA_DATE_YEAR_MIN

#ifndef EYA_DATE_YEAR_MAX
/**
 * @def EYA_DATE_YEAR_MAX
 * @brief Maximum valid value for a year (maximum unsigned short value)
 * @details Represents the largest valid year value that can be represented
 *          by the eya_date_year_t type.
 */
#    define EYA_DATE_YEAR_MAX EYA_USHORT_MAX
#endif // EYA_DATE_YEAR_MAX

/**
 * @typedef eya_date_year_t
 * @brief Type representing a calendar year
 * @details This type is an alias for eya_ushort_t and represents years
 *          in the range [EYA_DATE_YEAR_MIN, EYA_DATE_YEAR_MAX].
 *          It is used to store and manipulate year values in date operations.
 */
typedef eya_ushort_t eya_date_year_t;

#endif // EYA_DATE_YEAR_H