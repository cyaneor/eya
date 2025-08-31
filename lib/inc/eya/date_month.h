/**
 * @file date_month.h
 * @brief Header file defining month constants and type for date operations
 * @details This file provides macros for month values (January to December)
 *          and related constants for use in date-related operations.
 *
 *          It defines the minimum and maximum valid month values
 *          and a type alias for representing months.
 */

#ifndef EYA_DATE_MONTH_H
#define EYA_DATE_MONTH_H

#include "date_month_index.h"

/**
 * @def EYA_DATE_MONTH_JANUARY
 * @brief January month representation.
 *
 * This macro defines the month value for January,
 * which is 1.
 */
#define EYA_DATE_MONTH_JANUARY (EYA_DATE_MONTH_INDEX_JANUARY + 1)

/**
 * @def EYA_DATE_MONTH_FEBRUARY
 * @brief February month representation.
 *
 * This macro defines the month value for February,
 * which is 2.
 */
#define EYA_DATE_MONTH_FEBRUARY (EYA_DATE_MONTH_INDEX_FEBRUARY + 1)

/**
 * @def EYA_DATE_MONTH_MARCH
 * @brief March month representation.
 *
 * This macro defines the month value for March,
 * which is 3.
 */
#define EYA_DATE_MONTH_MARCH (EYA_DATE_MONTH_INDEX_MARCH + 1)

/**
 * @def EYA_DATE_MONTH_APRIL
 * @brief April month representation.
 *
 * This macro defines the month value for April,
 * which is 4.
 */
#define EYA_DATE_MONTH_APRIL (EYA_DATE_MONTH_INDEX_APRIL + 1)

/**
 * @def EYA_DATE_MONTH_MAY
 * @brief May month representation.
 *
 * This macro defines the month value for May,
 * which is 5.
 */
#define EYA_DATE_MONTH_MAY (EYA_DATE_MONTH_INDEX_MAY + 1)

/**
 * @def EYA_DATE_MONTH_JUNE
 * @brief June month representation.
 *
 * This macro defines the month value for June,
 * which is 6.
 */
#define EYA_DATE_MONTH_JUNE (EYA_DATE_MONTH_INDEX_JUNE + 1)

/**
 * @def EYA_DATE_MONTH_JULY
 * @brief July month representation.
 *
 * This macro defines the month value for July,
 * which is 7.
 */
#define EYA_DATE_MONTH_JULY (EYA_DATE_MONTH_INDEX_JULY + 1)

/**
 * @def EYA_DATE_MONTH_AUGUST
 * @brief August month representation.
 *
 * This macro defines the month value for August,
 * which is 8.
 */
#define EYA_DATE_MONTH_AUGUST (EYA_DATE_MONTH_INDEX_AUGUST + 1)

/**
 * @def EYA_DATE_MONTH_SEPTEMBER
 * @brief September month representation.
 *
 * This macro defines the month value for September,
 * which is 9.
 */
#define EYA_DATE_MONTH_SEPTEMBER (EYA_DATE_MONTH_INDEX_SEPTEMBER + 1)

/**
 * @def EYA_DATE_MONTH_OCTOBER
 * @brief October month representation.
 *
 * This macro defines the month value for October,
 * which is 10.
 */
#define EYA_DATE_MONTH_OCTOBER (EYA_DATE_MONTH_INDEX_OCTOBER + 1)

/**
 * @def EYA_DATE_MONTH_NOVEMBER
 * @brief November month representation.
 *
 * This macro defines the month value for November,
 * which is 11.
 */
#define EYA_DATE_MONTH_NOVEMBER (EYA_DATE_MONTH_INDEX_NOVEMBER + 1)

/**
 * @def EYA_DATE_MONTH_DECEMBER
 * @brief December month representation.
 *
 * This macro defines the month value for December,
 * which is 12.
 */
#define EYA_DATE_MONTH_DECEMBER (EYA_DATE_MONTH_INDEX_DECEMBER + 1)

/**
 * @def EYA_DATE_MONTH_T_MIN
 * @brief Minimum month value.
 *
 * This macro defines the minimum valid month value,
 * which is January (1).
 */
#define EYA_DATE_MONTH_T_MIN EYA_DATE_MONTH_JANUARY

/**
 * @def EYA_DATE_MONTH_T_MAX
 * @brief Maximum month value.
 *
 * This macro defines the maximum valid month value,
 * which is December (12).
 */
#define EYA_DATE_MONTH_T_MAX EYA_DATE_MONTH_DECEMBER

/**
 * @typedef eya_date_month_t
 * @brief Typedef for representing the month.
 *
 * This typedef defines the type used for representing months,
 * using the underlying month index type.
 */
typedef eya_date_month_index_t eya_date_month_t;

#endif // EYA_DATE_MONTH_H
