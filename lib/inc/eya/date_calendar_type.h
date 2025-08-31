/**
 * @file date_calendar_type.h
 * @brief Defines macros for calendar types used in date handling.
 * @details This header file provides macros representing different calendar systems
 *          for use in date-related calculations or conversions.
 */

#ifndef EYA_DATE_CALENDAR_TYPE_H
#define EYA_DATE_CALENDAR_TYPE_H

#include "numeric.h"

/**
 * @def EYA_DATE_CALENDAR_GREGORIAN
 * @brief Represents the Gregorian calendar.
 * @details The Gregorian calendar is the widely used calendar system in most parts of the world.
 */
#define EYA_DATE_CALENDAR_GREGORIAN 0

/**
 * @def EYA_DATE_CALENDAR_JULIAN
 * @brief Represents the Julian calendar.
 * @details The Julian calendar is a historical calendar system used before the Gregorian calendar.
 */
#define EYA_DATE_CALENDAR_JULIAN 1

/**
 * @def EYA_DATE_CALENDAR_ISLAMIC
 * @brief Represents the Islamic (Hijri) calendar.
 * @details The Islamic calendar is a lunar-based calendar used in many Muslim-majority regions.
 */
#define EYA_DATE_CALENDAR_ISLAMIC 2

/**
 * @def EYA_DATE_CALENDAR_HEBREW
 * @brief Represents the Hebrew calendar.
 * @details The Hebrew calendar is a lunisolar calendar used in Jewish communities.
 */
#define EYA_DATE_CALENDAR_HEBREW 3

/**
 * @def EYA_DATE_CALENDAR_CHINESE
 * @brief Represents the Chinese calendar.
 * @details The Chinese calendar is a lunisolar calendar used in Chinese culture.
 */
#define EYA_DATE_CALENDAR_CHINESE 4

/**
 * @typedef eya_date_calendar_t
 * @brief Type alias for calendar type representation.
 * @details This type is used to represent the calendar system in date-related operations.
 */
typedef eya_uchar_t eya_date_calendar_t;

#endif // EYA_DATE_CALENDAR_TYPE_H