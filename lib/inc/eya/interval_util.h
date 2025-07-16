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
 * @def eya_interval_closed_is_valid
 * @brief Checks if a closed interval is valid.
 *
 * @param lower Lower bound of the interval.
 * @param upper Upper bound of the interval.
 *
 * @return Returns the value of expression `lower <= upper`,
 *         which is true if the interval is valid.
 */
#define eya_interval_closed_is_valid(lower, upper) ((lower) <= (upper))

/**
 * @def eya_interval_lopen_is_valid
 * @brief Checks if a left-open interval is valid.
 *
 * @param lower Lower bound of the interval.
 * @param upper Upper bound of the interval.
 *
 * @return Returns the value of expression `lower < upper`,
 *         which is true if the interval is valid.
 */
#define eya_interval_lopen_is_valid(lower, upper) ((lower) < (upper))

/**
 * @def eya_interval_ropen_is_valid
 * @brief Checks if a right-open interval is valid.
 *
 * @param lower Lower bound of the interval.
 * @param upper Upper bound of the interval.
 *
 * @return Returns the value of expression `lower < upper`,
 *         which is true if the interval is valid.
 */
#define eya_interval_ropen_is_valid(lower, upper) ((lower) < (upper))

/**
 * @def eya_interval_open_is_valid
 * @brief Checks if an open interval is valid.
 *
 * @param lower Lower bound of the interval.
 * @param upper Upper bound of the interval.
 *
 * @return Returns the value of expression `lower < upper`,
 *         which is true if the interval is valid.
 */
#define eya_interval_open_is_valid(lower, upper) ((lower) < (upper))

/**
 * @def eya_interval_closed_contains_value
 * @brief Checks if a value is contained within a closed interval.
 *
 * @param lower Lower bound of the interval.
 * @param upper Upper bound of the interval.
 * @param value Value to check for interval membership.
 *
 * @return Returns `true` if the `value` lies within [lower, upper] interval,
 *         and `false` otherwise.
 */
#define eya_interval_closed_contains_value(lower, upper, value)                                    \
    ((value) >= (lower) && (value) <= (upper))

/**
 * @def eya_interval_lopen_contains_value
 * @brief Checks if a value is contained within a left-open interval.
 *
 * @param lower Lower bound of the interval.
 * @param upper Upper bound of the interval.
 * @param value Value to check for interval membership.
 *
 * @return Returns `true` if the `value` lies within (lower, upper] interval,
 *         and `false` otherwise.
 */
#define eya_interval_lopen_contains_value(lower, upper, value)                                     \
    ((value) > (lower) && (value) <= (upper))

/**
 * @def eya_interval_ropen_contains_value
 * @brief Checks if a value is contained within a right-open interval.
 *
 * @param lower Lower bound of the interval.
 * @param upper Upper bound of the interval.
 * @param value Value to check for interval membership.
 *
 * @return Returns `true` if the `value` lies within [lower, upper) interval,
 *         and `false` otherwise.
 */
#define eya_interval_ropen_contains_value(lower, upper, value)                                     \
    ((value) >= (lower) && (value) < (upper))

/**
 * @def eya_interval_open_contains_value
 * @brief Checks if a value is contained within an open interval.
 *
 * @param lower Lower bound of the interval.
 * @param upper Upper bound of the interval.
 * @param value Value to check for interval membership.
 *
 * @return Returns `true` if the `value` lies within (lower, upper) interval,
 *         and `false` otherwise.
 */
#define eya_interval_open_contains_value(lower, upper, value)                                      \
    ((value) > (lower) && (value) < (upper))

/**
 * @def eya_interval_closed_contains_range
 * @brief Checks if a closed interval contains another closed interval.
 *
 * @param r1_lower Lower bound of the containing interval.
 * @param r1_upper Upper bound of the containing interval.
 * @param r2_lower Lower bound of the contained interval.
 * @param r2_upper Upper bound of the contained interval.
 *
 * @return Returns `true` if the interval [r2_lower, r2_upper] is contained
 *         within [r1_lower, r1_upper], and `false` otherwise.
 */
#define eya_interval_closed_contains_range(r1_lower, r1_upper, r2_lower, r2_upper)                 \
    ((r1_lower) <= (r2_lower) && (r2_upper) <= (r1_upper))

/**
 * @def eya_interval_lopen_contains_range
 * @brief Checks if a left-open interval contains another left-open interval.
 *
 * @param r1_lower Lower bound of the containing interval.
 * @param r1_upper Upper bound of the containing interval.
 * @param r2_lower Lower bound of the contained interval.
 * @param r2_upper Upper bound of the contained interval.
 *
 * @return Returns `true` if the interval (r2_lower, r2_upper] is contained
 *         within (r1_lower, r1_upper], and `false` otherwise.
 */
#define eya_interval_lopen_contains_range(r1_lower, r1_upper, r2_lower, r2_upper)                  \
    ((r1_lower) < (r2_lower) && (r2_upper) <= (r1_upper))

/**
 * @def eya_interval_ropen_contains_range
 * @brief Checks if a right-open interval contains another right-open interval.
 *
 * @param r1_lower Lower bound of the containing interval.
 * @param r1_upper Upper bound of the containing interval.
 * @param r2_lower Lower bound of the contained interval.
 * @param r2_upper Upper bound of the contained interval.
 *
 * @return Returns `true` if the interval [r2_lower, r2_upper) is contained
 *         within [r1_lower, r1_upper), and `false` otherwise.
 */
#define eya_interval_ropen_contains_range(r1_lower, r1_upper, r2_lower, r2_upper)                  \
    ((r1_lower) <= (r2_lower) && (r2_upper) < (r1_upper))

/**
 * @def eya_interval_open_contains_range
 * @brief Checks if an open interval contains another open interval.
 *
 * @param r1_lower Lower bound of the containing interval.
 * @param r1_upper Upper bound of the containing interval.
 * @param r2_lower Lower bound of the contained interval.
 * @param r2_upper Upper bound of the contained interval.
 *
 * @return Returns `true` if the interval (r2_lower, r2_upper) is contained
 *         within (r1_lower, r1_upper), and `false` otherwise.
 */
#define eya_interval_open_contains_range(r1_lower, r1_upper, r2_lower, r2_upper)                   \
    ((r1_lower) < (r2_lower) && (r2_upper) < (r1_upper))

#endif // EYA_INTERVAL_UTIL_H