/**
 * @file interval_util.h
 * @brief Interval validation and containment utilities
 *
 * This header provides utility macros
 * for working with mathematical intervals of different types.
 *
 * It includes functions for checking interval validity
 * and value containment in:
 *
 *   - Closed intervals [a, b]
 *   - Left-open intervals (a, b]
 *   - Right-open intervals [a, b)
 *   - Open intervals (a, b)
 *
 * All macros are implemented
 * as efficient boolean expressions suitable for any context.
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
 * @return Returns the value of expression `lower <= upper`,
 *         which is true if the interval is valid.
 */
#define eya_interval_ropen_is_valid(lower, upper) ((lower) <= (upper))

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
 * @def eya_interval_closed_contains
 * @brief Checks if a value is contained within a closed interval.
 *
 * @param lower Lower bound of the interval.
 * @param upper Upper bound of the interval.
 * @param value Value to check for interval membership.
 *
 * @return Returns `true` if the `value` lies within [lower, upper] interval,
 *         and `false` otherwise.
 */
#define eya_interval_closed_contains(lower, upper, value) ((value) >= (lower) && (value) <= (upper))

/**
 * @def eya_interval_lopen_contains
 * @brief Checks if a value is contained within a left-open interval.
 *
 * @param lower Lower bound of the interval.
 * @param upper Upper bound of the interval.
 * @param value Value to check for interval membership.
 *
 * @return Returns `true` if the `value` lies within (lower, upper] interval,
 *         and `false` otherwise.
 */
#define eya_interval_lopen_contains(lower, upper, value) ((value) > (lower) && (value) <= (upper))

/**
 * @def eya_interval_ropen_contains
 * @brief Checks if a value is contained within a right-open interval.
 *
 * @param lower Lower bound of the interval.
 * @param upper Upper bound of the interval.
 * @param value Value to check for interval membership.
 *
 * @return Returns `true` if the `value` lies within [lower, upper) interval,
 *         and `false` otherwise.
 */
#define eya_interval_ropen_contains(lower, upper, value) ((value) >= (lower) && (value) < (upper))

/**
 * @def eya_interval_open_contains
 * @brief Checks if a value is contained within an open interval.
 *
 * @param lower Lower bound of the interval.
 * @param upper Upper bound of the interval.
 * @param value Value to check for interval membership.
 *
 * @return Returns `true` if the `value` lies within (lower, upper) interval,
 *         and `false` otherwise.
 */
#define eya_interval_open_contains(lower, upper, value) ((value) > (lower) && (value) < (upper))

#endif // EYA_INTERVAL_UTIL_H