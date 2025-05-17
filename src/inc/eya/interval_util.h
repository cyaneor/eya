/**
 * @file interval_util.h
 * @brief A set of macros for interval operations.
 *
 * This file contains macros for validating intervals with different boundary
 * types (closed, open, left-open, right-open) and for checking if a value is
 * contained within an interval with specified boundary types.
 *
 * The macros provide an easy way to check whether an interval
 * is valid and whether a value is contained within an interval
 * considering boundary types.
 */

#ifndef EYA_INTERVAL_UTIL_H
#define EYA_INTERVAL_UTIL_H

/**
 * @def eya_interval_is_valid_closed
 * @brief Checks if a closed interval is valid.
 *
 * @param lower Lower bound of the interval.
 * @param upper Upper bound of the interval.
 *
 * @return Returns the value of expression `lower <= upper`,
 *         which is true if the interval is valid.
 */
#define eya_interval_is_valid_closed(lower, upper) ((lower) <= (upper))

/**
 * @def eya_interval_is_valid_lopen
 * @brief Checks if a left-open interval is valid.
 *
 * @param lower Lower bound of the interval.
 * @param upper Upper bound of the interval.
 *
 * @return Returns the value of expression `lower < upper`,
 *         which is true if the interval is valid.
 */
#define eya_interval_is_valid_lopen(lower, upper) ((lower) < (upper))

/**
 * @def eya_interval_is_valid_ropen
 * @brief Checks if a right-open interval is valid.
 *
 * @param lower Lower bound of the interval.
 * @param upper Upper bound of the interval.
 *
 * @return Returns the value of expression `lower <= upper`,
 *         which is true if the interval is valid.
 */
#define eya_interval_is_valid_ropen(lower, upper) ((lower) <= (upper))

/**
 * @def eya_interval_is_valid_open
 * @brief Checks if an open interval is valid.
 *
 * @param lower Lower bound of the interval.
 * @param upper Upper bound of the interval.
 *
 * @return Returns the value of expression `lower < upper`,
 *         which is true if the interval is valid.
 */
#define eya_interval_is_valid_open(lower, upper) ((lower) < (upper))

/**
 * @def eya_interval_is_within_closed
 * @brief Checks if a value is contained within a closed interval.
 *
 * @param lower Lower bound of the interval.
 * @param upper Upper bound of the interval.
 * @param value Value to check for interval membership.
 *
 * @return Returns `true` if the `value` lies within [lower, upper] interval,
 *         and `false` otherwise.
 */
#define eya_interval_is_within_closed(lower, upper, value)                                         \
    ((value) >= (lower) && (value) <= (upper))

/**
 * @def eya_interval_is_within_lopen
 * @brief Checks if a value is contained within a left-open interval.
 *
 * @param lower Lower bound of the interval.
 * @param upper Upper bound of the interval.
 * @param value Value to check for interval membership.
 *
 * @return Returns `true` if the `value` lies within (lower, upper] interval,
 *         and `false` otherwise.
 */
#define eya_interval_is_within_lopen(lower, upper, value) ((value) > (lower) && (value) <= (upper))

/**
 * @def eya_interval_is_within_ropen
 * @brief Checks if a value is contained within a right-open interval.
 *
 * @param lower Lower bound of the interval.
 * @param upper Upper bound of the interval.
 * @param value Value to check for interval membership.
 *
 * @return Returns `true` if the `value` lies within [lower, upper) interval,
 *         and `false` otherwise.
 */
#define eya_interval_is_within_ropen(lower, upper, value) ((value) >= (lower) && (value) < (upper))

/**
 * @def eya_interval_is_within_open
 * @brief Checks if a value is contained within an open interval.
 *
 * @param lower Lower bound of the interval.
 * @param upper Upper bound of the interval.
 * @param value Value to check for interval membership.
 *
 * @return Returns `true` if the `value` lies within (lower, upper) interval,
 *         and `false` otherwise.
 */
#define eya_interval_is_within_open(lower, upper, value) ((value) > (lower) && (value) < (upper))

/**
 * @def eya_interval_contains_closed
 * @brief Checks if a second closed interval
 *        is contained within the first closed interval.
 */
#define eya_interval_contains_closed(outer_lower, outer_upper, inner_lower, inner_upper)           \
    (eya_interval_is_within_closed((outer_lower), (outer_upper), (inner_lower)) &&                 \
     eya_interval_is_within_closed((outer_lower), (outer_upper), (inner_upper)))

/**
 * @def eya_interval_contains_open
 * @brief Checks if a second open interval
 *        is contained within the first open interval.
 */
#define eya_interval_contains_open(outer_lower, outer_upper, inner_lower, inner_upper)             \
    (eya_interval_is_within_open((outer_lower), (outer_upper), (inner_lower)) &&                   \
     eya_interval_is_within_open((outer_lower), (outer_upper), (inner_upper)))

/**
 * @def eya_interval_contains_lopen
 * @brief Checks if a second left-open interval
 *        is contained within the first interval.
 */
#define eya_interval_contains_lopen(outer_lower, outer_upper, inner_lower, inner_upper)            \
    (eya_interval_is_within_lopen((outer_lower), (outer_upper), (inner_lower)) &&                  \
     eya_interval_is_within_lopen((outer_lower), (outer_upper), (inner_upper)))

/**
 * @def eya_interval_contains_ropen
 * @brief Checks if a second right-open interval
 *        is contained within the first interval.
 */
#define eya_interval_contains_ropen(outer_lower, outer_upper, inner_lower, inner_upper)            \
    (eya_interval_is_within_ropen((outer_lower), (outer_upper), (inner_lower)) &&                  \
     eya_interval_is_within_ropen((outer_lower), (outer_upper), (inner_upper)))

#endif // EYA_INTERVAL_UTIL_H