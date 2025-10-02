/**
 * @file interval_flags.h
 * @brief Interval flags enumeration and definitions.
 *
 * This header defines the `eya_interval_flags` type
 * and constants representing interval boundary openness.
 *
 * The flags distinguish between:
 * - Closed intervals [a, b]
 * - Left-open intervals (a, b]
 * - Right-open intervals [a, b)
 * - Fully open intervals (a, b)
 *
 * @note When using these flags, perform proper bitwise operations
 *       to check for left or right openness.
 */

#ifndef EYA_INTERVAL_FLAGS_H
#define EYA_INTERVAL_FLAGS_H

#include <eya/numeric_types.h>

/**
 * @enum
 * @brief Interval boundary flags.
 *
 * Flags for indicating which sides of an interval are open or closed.
 */
enum
{
    /**
     * @var EYA_INTERVAL_FLAGS_CLOSED
     * @brief Closed interval [a, b].
     * @details Both left and right boundaries are closed.
     */
    EYA_INTERVAL_FLAGS_CLOSED = 0,

    /**
     * @var EYA_INTERVAL_FLAGS_OPEN_LEFT
     * @brief Left-open interval (a, b].
     * @details The left boundary is open, the right boundary is closed.
     */
    EYA_INTERVAL_FLAGS_OPEN_LEFT = (1 << 1),

    /**
     * @var EYA_INTERVAL_FLAGS_OPEN_RIGHT
     * @brief Right-open interval [a, b).
     * @details The left boundary is closed, the right boundary is open.
     */
    EYA_INTERVAL_FLAGS_OPEN_RIGHT = (1 << 2),

    /**
     * @var EYA_INTERVAL_FLAGS_OPEN
     * @brief Fully open interval (a, b).
     * @details Both boundaries are open.
     *          Equivalent to (EYA_INTERVAL_FLAGS_OPEN_LEFT | EYA_INTERVAL_FLAGS_OPEN_RIGHT).
     */
    EYA_INTERVAL_FLAGS_OPEN = (EYA_INTERVAL_FLAGS_OPEN_LEFT | EYA_INTERVAL_FLAGS_OPEN_RIGHT),
};

/**
 * @typedef eya_interval_flags
 * @brief Type used to store interval flags.
 */
typedef eya_uchar_t eya_interval_flags;

#endif // EYA_INTERVAL_FLAGS_H
