/**
 * @file numeric_interval_util.h
 * @brief Utility macros for working with numeric intervals.
 *
 * This header provides a set of macros for manipulating and querying numeric intervals.
 * The intervals can be closed, open-left, open-right, or fully open, as specified by
 * the interval flags defined in `eya/interval_flags.h`.
 *
 * The macros support operations such as checking if a value or range is within an interval,
 * computing effective bounds, calculating interval size and capacity,
 * and wrapping values within an interval.
 *
 * @note All macros assume that the input bounds and values are of compatible numeric types
 *       (e.g., `int`, `long`). The behavior is undefined if the inputs are invalid or
 *       inconsistent (e.g., `lower > upper`).
 *
 * @see interval_flags.h
 */

#ifndef EYA_NUMERIC_INTERVAL_UTIL_H
#define EYA_NUMERIC_INTERVAL_UTIL_H

#include <eya/interval_flags.h>

/**
 * @def eya_numeric_interval_contains_value(flags, lower, value, upper)
 * @brief Checks if a value is within a numeric interval based on the specified boundary flags.
 *
 * This macro determines whether the `value` lies within the interval defined
 * by `lower` and `upper` bounds, according to the interval type specified by `flags`.
 * The interval can be closed, open on the left, open on the right, or fully open.
 *
 * @param flags The type of interval. Possible values:
 *              - EYA_INTERVAL_FLAGS_CLOSED:     [lower, upper] (inclusive on both ends)
 *              - EYA_INTERVAL_FLAGS_OPEN_LEFT:  (lower, upper] (exclusive lower, inclusive upper)
 *              - EYA_INTERVAL_FLAGS_OPEN_RIGHT: [lower, upper) (inclusive lower, exclusive upper)
 *              - EYA_INTERVAL_FLAGS_OPEN:       (lower, upper) (exclusive on both ends)
 *
 * @param lower The lower bound of the interval.
 * @param value The value to check.
 * @param upper The upper bound of the interval.
 * @return 1 if the value is within the interval, 0 otherwise.
 *
 * @note If an invalid `flags` value is provided, the macro returns 0.
 */
#define eya_numeric_interval_contains_value(flags, lower, value, upper)                            \
    (flags == EYA_INTERVAL_FLAGS_CLOSED       ? lower <= value && value <= upper                   \
     : flags == EYA_INTERVAL_FLAGS_OPEN_LEFT  ? lower < value && value <= upper                    \
     : flags == EYA_INTERVAL_FLAGS_OPEN_RIGHT ? lower <= value && value < upper                    \
     : flags == EYA_INTERVAL_FLAGS_OPEN       ? lower < value && value < upper                     \
                                              : 0)
/**
 * @def eya_numeric_interval_contains_range(flags, r1_lower, r1_upper, r2_lower, r2_upper)
 * @brief Checks if the interval `r2` is fully contained within `r1`.
 *
 * This macro determines whether the interval defined by `r2_lower` and `r2_upper`
 * is entirely contained within the interval defined by `r1_lower` and `r1_upper`,
 * based on the boundary type specified by `flags`.
 *
 * It uses the `eya_numeric_interval_contains_value` macro to check
 * if both the lower and upper bounds of the second interval lie
 * within the first interval.
 *
 * @param flags The type of interval. Possible values:
 *              - EYA_INTERVAL_FLAGS_CLOSED:
 *                [r1_lower, r1_upper] (inclusive on both ends)
 *              - EYA_INTERVAL_FLAGS_OPEN_LEFT:
 *                (r1_lower, r1_upper] (exclusive lower, inclusive upper)
 *              - EYA_INTERVAL_FLAGS_OPEN_RIGHT:
 *                [r1_lower, r1_upper) (inclusive lower, exclusive upper)
 *              - EYA_INTERVAL_FLAGS_OPEN:
 *                (r1_lower, r1_upper) (exclusive on both ends)
 *
 * @param r1_lower The lower bound of the containing interval.
 * @param r1_upper The upper bound of the containing interval.
 * @param r2_lower The lower bound of the interval to check.
 * @param r2_upper The upper bound of the interval to check.
 * @return 1 if the interval `r2` is fully contained within `r1`, 0 otherwise.
 *
 * @note This macro relies on `eya_numeric_interval_contains_value`
 *       to evaluate the inclusion of both `r2_lower` and `r2_upper`
 *       within the interval [r1_lower, r1_upper].
 *
 * @see eya_numeric_interval_contains_value
 */
#define eya_numeric_interval_contains_range(flags, r1_lower, r1_upper, r2_lower, r2_upper)         \
    (eya_numeric_interval_contains_value(flags, r1_lower, r2_lower, r1_upper) &&                   \
     eya_numeric_interval_contains_value(flags, r1_lower, r2_upper, r1_upper))

/**
 * @def eya_numeric_interval_lower(flags, lower)
 * @brief Returns the effective lower bound of an interval based on the specified boundary flags.
 *
 * This macro computes the effective lower bound of an interval,
 * adjusting the provided `lower` value based on the interval type specified by `flags`.
 *
 * For open-left or fully open intervals,
 * the lower bound is incremented by 1 to reflect the exclusive nature of the boundary.
 *
 * @param flags The type of interval.
 *              Possible values:
 *              - EYA_INTERVAL_FLAGS_CLOSED:     [lower, upper] (inclusive lower bound)
 *              - EYA_INTERVAL_FLAGS_OPEN_LEFT:  (lower, upper] (exclusive lower bound)
 *              - EYA_INTERVAL_FLAGS_OPEN_RIGHT: [lower, upper) (inclusive lower bound)
 *              - EYA_INTERVAL_FLAGS_OPEN:       (lower, upper) (exclusive lower bound)
 *
 * @param lower The nominal lower bound of the interval.
 * @return The effective lower bound of the interval.
 *         Returns 0 if an invalid `flags` value is provided.
 *
 * @note For open-left or fully open intervals,
 *       the lower bound is incremented by 1 to account for the exclusive boundary.
 *       For closed or open-right intervals, the lower bound remains unchanged.
 */
#define eya_numeric_interval_lower(flags, lower)                                                   \
    (flags == EYA_INTERVAL_FLAGS_CLOSED       ? lower                                              \
     : flags == EYA_INTERVAL_FLAGS_OPEN_LEFT  ? lower + 1                                          \
     : flags == EYA_INTERVAL_FLAGS_OPEN_RIGHT ? lower                                              \
     : flags == EYA_INTERVAL_FLAGS_OPEN       ? lower + 1                                          \
                                              : 0)

/**
 * @def eya_numeric_interval_upper(flags, upper)
 * @brief Returns the effective upper bound of an interval based on the specified boundary flags.
 *
 * This macro computes the effective upper bound of an interval,
 * adjusting the provided `upper` value based on the interval type specified by `flags`.
 *
 * For open-right or fully open intervals,
 * the upper bound is decremented by 1 to reflect the exclusive nature of the boundary.
 *
 * @param flags The type of interval. Possible values:
 *              - EYA_INTERVAL_FLAGS_CLOSED: [lower, upper] (inclusive upper bound)
 *              - EYA_INTERVAL_FLAGS_OPEN_LEFT: (lower, upper] (inclusive upper bound)
 *              - EYA_INTERVAL_FLAGS_OPEN_RIGHT: [lower, upper) (exclusive upper bound)
 *              - EYA_INTERVAL_FLAGS_OPEN: (lower, upper) (exclusive upper bound)
 *
 * @param upper The nominal upper bound of the interval.
 * @return The effective upper bound of the interval.
 *         Returns 0 if an invalid `flags` value is provided.
 *
 * @note For open-right or fully open intervals,
 *       the upper bound is decremented by 1 to account for the exclusive boundary.
 *       For closed or open-left intervals, the upper bound remains unchanged.
 */
#define eya_numeric_interval_upper(flags, upper)                                                   \
    (flags == EYA_INTERVAL_FLAGS_CLOSED       ? upper                                              \
     : flags == EYA_INTERVAL_FLAGS_OPEN_LEFT  ? upper                                              \
     : flags == EYA_INTERVAL_FLAGS_OPEN_RIGHT ? upper - 1                                          \
     : flags == EYA_INTERVAL_FLAGS_OPEN       ? upper - 1                                          \
                                              : 0)

/**
 * @def eya_numeric_interval_size(flags, lower, upper)
 * @brief Calculates the size of a numeric interval based on the specified boundary flags.
 *
 * This macro computes the size (length) of the interval defined by `lower` and `upper` bounds,
 * according to the interval type specified by `flags`.
 *
 * The size is determined by subtracting the effective lower bound
 * (obtained via `eya_numeric_interval_lower`) from the effective
 * upper bound (obtained via `eya_numeric_interval_upper`).
 *
 * @param flags The type of interval.
 *              Possible values:
 *              - EYA_INTERVAL_FLAGS_CLOSED:     [lower, upper] (inclusive on both ends)
 *              - EYA_INTERVAL_FLAGS_OPEN_LEFT:  (lower, upper] (exclusive lower, inclusive upper)
 *              - EYA_INTERVAL_FLAGS_OPEN_RIGHT: [lower, upper) (inclusive lower, exclusive upper)
 *              - EYA_INTERVAL_FLAGS_OPEN:       (lower, upper) (exclusive on both ends)
 *
 * @param lower The nominal lower bound of the interval.
 * @param upper The nominal upper bound of the interval.
 * @return The size of the interval,
 *         calculated as the difference between the effective upper and lower bounds.
 *
 * @note The macro relies on `eya_numeric_interval_lower` and `eya_numeric_interval_upper`
 *       to compute the effective bounds, which account for inclusive
 *       or exclusive boundaries based on `flags`.
 *
 * @see eya_numeric_interval_lower
 * @see eya_numeric_interval_upper
 */
#define eya_numeric_interval_size(flags, lower, upper)                                             \
    (eya_numeric_interval_upper(flags, upper) - eya_numeric_interval_lower(flags, lower))

/**
 * @def eya_numeric_interval_capacity(flags, lower, upper)
 * @brief Calculates the capacity of a numeric interval based on the specified boundary flags.
 *
 * This macro computes the capacity (number of integer values) of the interval defined
 * by `lower` and `upper` bounds, according to the interval type specified by `flags`.
 *
 * The capacity is determined by adding 1 to the interval size,
 * which is calculated using the `eya_numeric_interval_size` macro.
 *
 * This accounts for inclusive boundaries
 * where the endpoints are part of the interval.
 *
 * @param flags The type of interval. Possible values:
 *              - EYA_INTERVAL_FLAGS_CLOSED:     [lower, upper] (inclusive on both ends)
 *              - EYA_INTERVAL_FLAGS_OPEN_LEFT:  (lower, upper] (exclusive lower, inclusive upper)
 *              - EYA_INTERVAL_FLAGS_OPEN_RIGHT: [lower, upper) (inclusive lower, exclusive upper)
 *              - EYA_INTERVAL_FLAGS_OPEN:       (lower, upper) (exclusive on both ends)
 *
 * @param lower The nominal lower bound of the interval.
 * @param upper The nominal upper bound of the interval.
 * @return The capacity of the interval,
 *         calculated as the interval size plus 1.
 *
 * @note The macro relies on `eya_numeric_interval_size` to compute the interval size,
 *       which in turn uses `eya_numeric_interval_lower` and `eya_numeric_interval_upper`
 *       to determine the effective bounds.
 *
 * @see eya_numeric_interval_size
 * @see eya_numeric_interval_lower
 * @see eya_numeric_interval_upper
 */
#define eya_numeric_interval_capacity(flags, lower, upper)                                         \
    (eya_numeric_interval_size(flags, lower, upper) + 1)

/**
 * @def eya_numeric_interval_wrap_base(T, lower, upper, value, result, overflow)
 * @brief Wraps a value within a specified numeric interval and computes the overflow.
 *
 * This macro wraps the input `value` into the closed interval defined
 * by `lower` and `upper` bounds, assuming a closed interval ([lower, upper]).
 *
 * It calculates the wrapped value
 * and the number of times the value overflows or underflows the interval.
 * The result is stored in `result`, and the overflow count is stored in `overflow`.
 * The macro operates on a specified numeric type `T`.
 *
 * @param T The numeric type of the interval bounds, value, result, and overflow (e.g., int, long).
 * @param lower The lower bound of the closed interval.
 * @param upper The upper bound of the closed interval.
 * @param value The input value to be wrapped.
 * @param result The variable where the wrapped value (within [lower, upper]) is stored.
 * @param overflow The variable where the number of overflows (positive or negative) is stored.
 *
 * @note The macro assumes a closed interval ([lower, upper])
 *       and uses `eya_numeric_interval_capacity` and `eya_numeric_interval_contains_value`
 *       to compute the interval capacity and check value containment, respectively.
 *
 * @note If the interval capacity is 0 (i.e., lower == upper),
 *       the result is set to `lower`, and overflow is set to 0.
 *
 * @note For values outside the interval:
 *
 *       - If `value` is less than `lower`,
 *         the macro computes the wrapped value by calculating
 *         the offset from `lower` and determining the number of underflows.
 *
 *       - If `value` is greater than `upper`,
 *         the macro computes the wrapped value
 *         using modular arithmetic and determines the number of overflows.
 *
 * @note The macro uses a do-while(0) construct
 *       to ensure it can be safely used in any context.
 *
 * @see eya_numeric_interval_capacity
 * @see eya_numeric_interval_contains_value
 */
#define eya_numeric_interval_wrap_base(T, lower, upper, value, result, overflow)                   \
    do                                                                                             \
    {                                                                                              \
        T _capacity = eya_numeric_interval_capacity(EYA_INTERVAL_FLAGS_CLOSED, (lower), (upper));  \
                                                                                                   \
        if (_capacity == 0)                                                                        \
        {                                                                                          \
            (result)   = lower;                                                                    \
            (overflow) = 0;                                                                        \
        }                                                                                          \
        else if (eya_numeric_interval_contains_value(                                              \
                     EYA_INTERVAL_FLAGS_CLOSED, (lower), (value), (upper)))                        \
        {                                                                                          \
            (result)   = value;                                                                    \
            (overflow) = 0;                                                                        \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
            T _offset   = 0;                                                                       \
            T _result   = 0;                                                                       \
            T _overflow = 0;                                                                       \
                                                                                                   \
            if ((value) < (lower))                                                                 \
            {                                                                                      \
                T delta   = (lower) - (value);                                                     \
                _overflow = (delta + _capacity - 1) / _capacity;                                   \
                _result   = (upper) - ((delta - 1) % _capacity);                                   \
            }                                                                                      \
            else                                                                                   \
            {                                                                                      \
                _offset   = (value) - (lower);                                                     \
                _result   = _offset % _capacity;                                                   \
                _overflow = _offset / _capacity;                                                   \
                                                                                                   \
                if (_offset < 0)                                                                   \
                {                                                                                  \
                    _overflow = (_offset - _capacity + 1) / _capacity;                             \
                    _result   = _offset - _overflow * _capacity;                                   \
                }                                                                                  \
                _result += (lower);                                                                \
            }                                                                                      \
                                                                                                   \
            (result)   = _result;                                                                  \
            (overflow) = _overflow;                                                                \
        }                                                                                          \
    } while (0)

/**
 * @def eya_numeric_interval_wrap_to(T, flags, lower, upper, value, result, overflow)
 * @brief Wraps a value within a numeric interval
 *        with specified boundary types and computes overflow.
 *
 * This macro wraps the input `value` into the interval defined by `lower` and `upper` bounds,
 * respecting the interval type specified by `flags` (closed, open-left, open-right, or open).
 *
 * It adjusts the bounds using `eya_numeric_interval_lower` and `eya_numeric_interval_upper`
 * to account for inclusive or exclusive boundaries, then delegates to
 * `eya_numeric_interval_wrap_base` to perform the wrapping and compute the overflow.
 *
 * The wrapped value is stored in `result`,
 * and the number of overflows or underflows is stored in `overflow`.
 *
 * @param T The numeric type of the interval bounds, value,
 *          result, and overflow (e.g., int, long).
 * @param flags The type of interval.
 *              Possible values:
 *              - EYA_INTERVAL_FLAGS_CLOSED:     [lower, upper] (inclusive on both ends)
 *              - EYA_INTERVAL_FLAGS_OPEN_LEFT:  (lower, upper] (exclusive lower, inclusive upper)
 *              - EYA_INTERVAL_FLAGS_OPEN_RIGHT: [lower, upper) (inclusive lower, exclusive upper)
 *              - EYA_INTERVAL_FLAGS_OPEN:       (lower, upper) (exclusive on both ends)
 * @param lower The nominal lower bound of the interval.
 * @param upper The nominal upper bound of the interval.
 * @param value The input value to be wrapped.
 * @param result The variable where the wrapped value (within the effective interval) is stored.
 * @param overflow The variable where the number of overflows (positive or negative) is stored.
 *
 * @note This macro adjusts the interval bounds using `eya_numeric_interval_lower`
 *       and `eya_numeric_interval_upper` to handle the specified boundary types
 *       before calling `eya_numeric_interval_wrap_base` to perform the wrapping operation.
 *
 * @note The macro uses a do-while(0) construct
 *       to ensure it can be safely used in any context.
 *
 * @see eya_numeric_interval_lower
 * @see eya_numeric_interval_upper
 * @see eya_numeric_interval_wrap_base
 */
#define eya_numeric_interval_wrap_to(T, flags, lower, upper, value, result, overflow)              \
    do                                                                                             \
    {                                                                                              \
        T _lower = eya_numeric_interval_lower((flags), (lower));                                   \
        T _upper = eya_numeric_interval_upper((flags), (upper));                                   \
        eya_numeric_interval_wrap_base(T, _lower, _upper, (value), (result), (overflow));          \
    } while (0)

/**
 * @def eya_numeric_interval_wrap(T, flags, lower, upper, value, overflow)
 * @brief Wraps a value within a numeric interval and updates the value in place.
 *
 * This macro wraps the input `value` into the interval defined by `lower` and `upper` bounds,
 * according to the interval type specified by `flags` (closed, open-left, open-right, or open).
 * The wrapped value replaces the original `value`, and the number of overflows or underflows
 * is stored in `overflow`. It delegates to `eya_numeric_interval_wrap_to` to perform the
 * wrapping operation.
 *
 * @param T The numeric type of the interval bounds, value, and overflow (e.g., int, long).
 * @param flags The type of interval.
 *              Possible values:
 *              - EYA_INTERVAL_FLAGS_CLOSED:     [lower, upper] (inclusive on both ends)
 *              - EYA_INTERVAL_FLAGS_OPEN_LEFT:  (lower, upper] (exclusive lower, inclusive upper)
 *              - EYA_INTERVAL_FLAGS_OPEN_RIGHT: [lower, upper) (inclusive lower, exclusive upper)
 *              - EYA_INTERVAL_FLAGS_OPEN:       (lower, upper) (exclusive on both ends)
 * @param lower The nominal lower bound of the interval.
 * @param upper The nominal upper bound of the interval.
 * @param value The input value to be wrapped; updated in place with the wrapped value.
 * @param overflow The variable where the number of overflows (positive or negative) is stored.
 *
 * @note This macro uses `eya_numeric_interval_wrap_to` to perform the wrapping,
 *       passing `value` as both the input and the result variable,
 *       effectively updating `value` in place.
 *
 * @see eya_numeric_interval_wrap_to
 */
#define eya_numeric_interval_wrap(T, flags, lower, upper, value, overflow)                         \
    eya_numeric_interval_wrap_to(T, flags, lower, upper, value, value, overflow)

#endif // EYA_NUMERIC_INTERVAL_UTIL_H
