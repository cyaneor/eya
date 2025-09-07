/**
 * @file interval_util.h
 * @brief Utilities for validating and checking containment in mathematical intervals
 *
 * This header provides utility macros for working with mathematical intervals
 * of different types, including closed, left-open, right-open, and open intervals.
 *
 * It includes macros for:
 *   - Validating intervals ([a, b], (a, b], [a, b), (a, b))
 *   - Checking if a single value is contained within an interval
 *   - Checking if one interval is fully contained within another interval
 *
 * All macros are implemented as efficient boolean expressions suitable for any context.
 *
 * @note Parameters must be comparable using relational operators
 * @warning Arguments are evaluated multiple times - avoid side effects
 */

#ifndef EYA_INTERVAL_UTIL_H
#define EYA_INTERVAL_UTIL_H

/**
 * @def EYA_INTERVAL_TYPE_CLOSED
 * @brief Represents a closed interval [lower, upper].
 *
 * The interval includes both the lower and upper bounds.
 */
#define EYA_INTERVAL_TYPE_CLOSED 0

/**
 * @def EYA_INTERVAL_TYPE_LEFT_OPEN
 * @brief Represents a left-open interval (lower, upper].
 *
 * The interval excludes the lower bound but includes the upper bound.
 */
#define EYA_INTERVAL_TYPE_LEFT_OPEN 1

/**
 * @def EYA_INTERVAL_TYPE_LEFT_OPEN
 * @brief Represents a left-open interval (lower, upper].
 *
 * The interval excludes the lower bound but includes the upper bound.
 */
#define EYA_INTERVAL_TYPE_RIGHT_OPEN 2

/**
 * @def EYA_INTERVAL_TYPE_RIGHT_OPEN
 * @brief Represents a right-open interval [lower, upper).
 *
 * The interval includes the lower bound but excludes the upper bound.
 */
#define EYA_INTERVAL_TYPE_OPEN 3

/**
 * @def eya_interval_contains_value(interval_type, val, min, max)
 * @brief Checks if a value is within a specified interval type.
 *
 * This macro evaluates whether the value `val` lies
 * within the interval defined by `min` and `max`,
 * according to the type of interval specified by `interval_type`.
 *
 * @param interval_type The type of interval, one of:
 *                      - EYA_INTERVAL_TYPE_CLOSED       : [min, max]
 *                      - EYA_INTERVAL_TYPE_LEFT_OPEN    : (min, max]
 *                      - EYA_INTERVAL_TYPE_RIGHT_OPEN   : [min, max)
 *                      - EYA_INTERVAL_TYPE_OPEN         : (min, max)
 *
 * @param val The value to check.
 * @param min The lower bound of the interval.
 * @param max The upper bound of the interval.
 *
 * @return Non-zero if `val` is within the interval, zero otherwise.
 */
#define eya_interval_contains_value(interval_type, min, val, max)                                  \
    ((interval_type) == EYA_INTERVAL_TYPE_CLOSED       ? ((min) <= (val) && (val) <= (max))        \
     : (interval_type) == EYA_INTERVAL_TYPE_LEFT_OPEN  ? (min) < (val) && (val) <= (max)           \
     : (interval_type) == EYA_INTERVAL_TYPE_RIGHT_OPEN ? ((min) <= (val) && (val) < (max))         \
     : (interval_type) == EYA_INTERVAL_TYPE_OPEN       ? ((min) < (val) && (val) < (max))          \
                                                       : 0)

/**
 * @def eya_interval_contains_range(interval_type, r1_min, r1_max, r2_min, r2_max)
 * @brief Checks if one interval is completely contained within another interval.
 *
 * This macro evaluates whether the interval `[r1_min, r1_max]` is fully
 * contained within the interval `[r2_min, r2_max]`, taking into account
 * the type of interval specified by `interval_type`.
 *
 * @param interval_type The type of interval, one of:
 *                      - EYA_INTERVAL_TYPE_CLOSED       : [min, max]
 *                      - EYA_INTERVAL_TYPE_LEFT_OPEN    : (min, max]
 *                      - EYA_INTERVAL_TYPE_RIGHT_OPEN   : [min, max)
 *                      - EYA_INTERVAL_TYPE_OPEN         : (min, max)
 * @param r1_min The lower bound of the first interval (the one being checked for containment).
 * @param r1_max The upper bound of the first interval.
 * @param r2_min The lower bound of the second interval (the container interval).
 * @param r2_max The upper bound of the second interval.
 *
 * @return Non-zero if `[r1_min, r1_max]` is completely contained in
 *         `[r2_min, r2_max]` according to `interval_type`, zero otherwise.
 */
#define eya_interval_contains_range(interval_type, r1_min, r1_max, r2_min, r2_max)                 \
    (eya_interval_contains_value(interval_type, r1_min, r2_min, r1_max) &&                         \
     eya_interval_contains_value(interval_type, r1_min, r2_max, r1_max))

/**
 * @def eya_interval_min(interval_type, min)
 * @brief Calculates the inclusive minimum value of an interval based on its type.
 *
 * This macro determines the actual minimum value that belongs to the interval,
 * adjusting for open/closed interval types.
 *
 * @param interval_type The type of interval from the EYA_INTERVAL_TYPE enumeration:
 *        - EYA_INTERVAL_TYPE_CLOSED: [min, max] - both endpoints included
 *        - EYA_INTERVAL_TYPE_LEFT_OPEN: (min, max] - left endpoint excluded
 *        - EYA_INTERVAL_TYPE_RIGHT_OPEN: [min, max) - right endpoint excluded
 *        - EYA_INTERVAL_TYPE_OPEN: (min, max) - both endpoints excluded
 * @param min The original minimum value of the interval
 *
 * @return The inclusive minimum value that actually belongs to the interval:
 *         - For CLOSED and RIGHT_OPEN: returns min
 *         - For LEFT_OPEN and OPEN: returns min + 1 (excludes the original min)
 *         - For unknown interval types: returns 0
 *
 * @note The returned value represents the smallest integer
 *       that is actually contained within the interval.
 */
#define eya_interval_min(interval_type, min)                                                       \
    ((interval_type) == EYA_INTERVAL_TYPE_CLOSED       ? (min)                                     \
     : (interval_type) == EYA_INTERVAL_TYPE_LEFT_OPEN  ? (min) + 1                                 \
     : (interval_type) == EYA_INTERVAL_TYPE_RIGHT_OPEN ? (min)                                     \
     : (interval_type) == EYA_INTERVAL_TYPE_OPEN       ? (min) + 1                                 \
                                                       : 0)

/**
 * @def eya_interval_max(interval_type, max)
 * @brief Calculates the inclusive maximum value of an interval based on its type.
 *
 * This macro determines the actual maximum value that belongs to the interval,
 * adjusting for open/closed interval types.
 *
 * @param interval_type The type of interval from the EYA_INTERVAL_TYPE enumeration:
 *        - EYA_INTERVAL_TYPE_CLOSED: [min, max] - both endpoints included
 *        - EYA_INTERVAL_TYPE_LEFT_OPEN: (min, max] - left endpoint excluded
 *        - EYA_INTERVAL_TYPE_RIGHT_OPEN: [min, max) - right endpoint excluded
 *        - EYA_INTERVAL_TYPE_OPEN: (min, max) - both endpoints excluded
 * @param max The original maximum value of the interval
 *
 * @return The inclusive maximum value that actually belongs to the interval:
 *         - For CLOSED and LEFT_OPEN: returns max
 *         - For RIGHT_OPEN and OPEN: returns max - 1 (excludes the original max)
 *         - For unknown interval types: returns 0
 *
 * @note The returned value represents the largest integer
 *       that is actually contained within the interval.
 */
#define eya_interval_max(interval_type, max)                                                       \
    ((interval_type) == EYA_INTERVAL_TYPE_CLOSED       ? (max)                                     \
     : (interval_type) == EYA_INTERVAL_TYPE_LEFT_OPEN  ? (max)                                     \
     : (interval_type) == EYA_INTERVAL_TYPE_RIGHT_OPEN ? (max)-1                                   \
     : (interval_type) == EYA_INTERVAL_TYPE_OPEN       ? (max)-1                                   \
                                                       : 0)

/**
 * @def eya_interval_size(interval_type, min, max)
 * @brief Calculates the size (cardinality) of an interval.
 *
 * This macro calculates the number of discrete integer values
 * contained within the specified interval type.
 *
 * For integer intervals, this represents
 * the count of values between the bounds.
 *
 * @param interval_type The type of interval, one of:
 *                      - EYA_INTERVAL_TYPE_CLOSED       : [min, max]
 *                      - EYA_INTERVAL_TYPE_LEFT_OPEN    : (min, max]
 *                      - EYA_INTERVAL_TYPE_RIGHT_OPEN   : [min, max)
 *                      - EYA_INTERVAL_TYPE_OPEN         : (min, max)
 * @param min The lower bound of the interval.
 * @param max The upper bound of the interval.
 *
 * @return The number of integer values in the interval, or 0 if the interval is invalid.
 *         Returns (max - min + 1) for closed intervals,
 *         (max - min) for left-open and right-open intervals,
 *         (max - min - 1) for open intervals.
 *
 * @note This macro is designed for integer intervals.
 *       For floating-point intervals,
 *       the concept of "size" may be different.
 *
 * @warning The result may be negative if max < min, indicating an invalid interval
 * @warning Arguments are evaluated multiple times - avoid expressions with side effects
 */
#define eya_interval_size(interval_type, min, max)                                                 \
    (eya_interval_max(interval_type, max) - eya_interval_min(interval_type, min) + 1)

#endif // EYA_INTERVAL_UTIL_H