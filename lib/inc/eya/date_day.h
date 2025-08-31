/**
 * @file date_day.h
 * @brief Header file defining day-of-month constants and type for date operations
 * @details This file provides the macro for the minimum day value of a month
 *          and a type alias for representing days of the month.
 *
 *          It is used in date-related operations to ensure
 *          consistent representation of days.
 */

#ifndef EYA_DATE_DAY_H
#define EYA_DATE_DAY_H

#include "numeric.h"

/**
 * @def EYA_DATE_DAY_MIN
 * @brief Minimum value for a day of the month.
 *
 * The `EYA_DATE_DAY_MIN` macro defines the minimum number of days
 * in any given month, which is always 1.
 */
#define EYA_DATE_DAY_MIN 1

/**
 * @typedef date_day_t
 * @brief Typedef for representing the day of the month.
 *
 * The `date_day_t` type is used for storing the day of the month as an unsigned char.
 * It is typically used in date-related operations to ensure consistency and readability.
 */
typedef eya_uchar_t date_day_t;

#endif // EYA_DATE_DAY_H
