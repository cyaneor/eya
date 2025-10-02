/**
 * @file interval_type.h
 * @brief Interval type enumeration and definitions.
 *
 * This header defines the `eya_interval_type` type
 * and constants representing the type of interval boundaries (open or closed).
 *
 * The enumeration distinguishes between:
 * - Closed intervals [a, b]
 * - Left-open intervals (a, b]
 * - Right-open intervals [a, b)
 * - Fully open intervals (a, b)
 *
 * @note When using these flags, ensure correct bitwise operations
 *       to check for left or right openness.
 */

#ifndef EYA_INTERVAL_TYPE_H
#define EYA_INTERVAL_TYPE_H

#include <eya/numeric_types.h>

enum
{
    /**
     * @var EYA_INTERVAL_TYPE_CLOSED
     * @brief Closed interval [a, b].
     * @details Both boundaries are closed.
     */
    EYA_INTERVAL_TYPE_CLOSED = 0,

    /**
     * @var EYA_INTERVAL_TYPE_OPEN_LEFT
     * @brief Left-open interval (a, b].
     * @details The left boundary is open, the right boundary is closed.
     */
    EYA_INTERVAL_TYPE_OPEN_LEFT = (1 << 1),

    /**
     * @var EYA_INTERVAL_TYPE_OPEN_RIGHT
     * @brief Right-open interval [a, b).
     * @details The left boundary is closed, the right boundary is open.
     */
    EYA_INTERVAL_TYPE_OPEN_RIGHT = (1 << 2),

    /**
     * @var EYA_INTERVAL_TYPE_OPEN
     * @brief Fully open interval (a, b).
     * @details Both boundaries are open.
     *          Combines ::EYA_INTERVAL_TYPE_OPEN_LEFT and ::EYA_INTERVAL_TYPE_OPEN_RIGHT.
     */
    EYA_INTERVAL_TYPE_OPEN =
        (EYA_INTERVAL_TYPE_CLOSED | EYA_INTERVAL_TYPE_OPEN_LEFT | EYA_INTERVAL_TYPE_OPEN_RIGHT),
};

/**
 * @typedef eya_interval_type
 * @brief Type for storing interval flags.
 */
typedef eya_uchar_t eya_interval_type;

#endif // EYA_INTERVAL_TYPE_H
