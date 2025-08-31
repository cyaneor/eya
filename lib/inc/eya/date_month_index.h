/**
 * @file date_month_index.h
 * @brief Header file defining month index constants and type for date operations
 * @details This file provides macros for month indexes (January to December)
 *          and related constants for use in date-related operations.
 *
 *          It defines the minimum and maximum valid month indexes,
 *          the total number of months in a year,
 *          and a type alias for representing month indexes.
 */

#ifndef EYA_DATE_MONTH_INDEX_H
#define EYA_DATE_MONTH_INDEX_H

#include "numeric.h"

/**
 * @def EYA_DATE_MONTH_INDEX_JANUARY
 * @brief Index for January.
 *
 * This macro defines the index value for January,
 * which is 0.
 */
#define EYA_DATE_MONTH_INDEX_JANUARY 0

/**
 * @def EYA_DATE_MONTH_INDEX_FEBRUARY
 * @brief Index for February.
 *
 * This macro defines the index value for February,
 * which is 1.
 */
#define EYA_DATE_MONTH_INDEX_FEBRUARY 1

/**
 * @def EYA_DATE_MONTH_INDEX_MARCH
 * @brief Index for March.
 *
 * This macro defines the index value for March,
 * which is 2.
 */
#define EYA_DATE_MONTH_INDEX_MARCH 2

/**
 * @def EYA_DATE_MONTH_INDEX_APRIL
 * @brief Index for April.
 *
 * This macro defines the index value for April,
 * which is 3.
 */
#define EYA_DATE_MONTH_INDEX_APRIL 3

/**
 * @def EYA_DATE_MONTH_INDEX_MAY
 * @brief Index for May.
 *
 * This macro defines the index value for May,
 * which is 4.
 */
#define EYA_DATE_MONTH_INDEX_MAY 4

/**
 * @def EYA_DATE_MONTH_INDEX_JUNE
 * @brief Index for June.
 *
 * This macro defines the index value for June,
 * which is 5.
 */
#define EYA_DATE_MONTH_INDEX_JUNE 5

/**
 * @def EYA_DATE_MONTH_INDEX_JULY
 * @brief Index for July.
 *
 * This macro defines the index value for July,
 * which is 6.
 */
#define EYA_DATE_MONTH_INDEX_JULY 6

/**
 * @def EYA_DATE_MONTH_INDEX_AUGUST
 * @brief Index for August.
 *
 * This macro defines the index value for August,
 * which is 7.
 */
#define EYA_DATE_MONTH_INDEX_AUGUST 7

/**
 * @def EYA_DATE_MONTH_INDEX_SEPTEMBER
 * @brief Index for September.
 *
 * This macro defines the index value for September,
 * which is 8.
 */
#define EYA_DATE_MONTH_INDEX_SEPTEMBER 8

/**
 * @def EYA_DATE_MONTH_INDEX_OCTOBER
 * @brief Index for October.
 *
 * This macro defines the index value for October,
 * which is 9.
 */
#define EYA_DATE_MONTH_INDEX_OCTOBER 9

/**
 * @def EYA_DATE_MONTH_INDEX_NOVEMBER
 * @brief Index for November.
 *
 * This macro defines the index value for November,
 * which is 10.
 */
#define EYA_DATE_MONTH_INDEX_NOVEMBER 10

/**
 * @def EYA_DATE_MONTH_INDEX_DECEMBER
 * @brief Index for December.
 *
 * This macro defines the index value for December,
 * which is 11.
 */
#define EYA_DATE_MONTH_INDEX_DECEMBER 11

/**
 * @def EYA_DATE_MONTH_INDEX_T_MIN
 * @brief Minimum month index.
 *
 * This macro defines the minimum valid month index,
 * which is January (0).
 */
#define EYA_DATE_MONTH_INDEX_T_MIN EYA_DATE_MONTH_INDEX_JANUARY

/**
 * @def EYA_DATE_MONTH_INDEX_T_MAX
 * @brief Maximum month index.
 *
 * This macro defines the maximum valid month index,
 * which is December (11).
 */
#define EYA_DATE_MONTH_INDEX_T_MAX EYA_DATE_MONTH_INDEX_DECEMBER

/**
 * @def EYA_DATE_MONTH_INDEXES_PER_YEAR
 * @brief Number of month indexes in a year.
 *
 * This macro defines the total number of month indexes in a year,
 * which is 12.
 */
#define EYA_DATE_MONTH_INDEXES_PER_YEAR (EYA_DATE_MONTH_INDEX_T_MAX + 1)

/**
 * @typedef eya_date_month_index_t
 * @brief Typedef for representing the month index.
 *
 * This typedef defines the type used for representing month indexes,
 * using an unsigned char integer type.
 */
typedef eya_uchar_t eya_date_month_index_t;

#endif // EYA_DATE_MONTH_INDEX_H
