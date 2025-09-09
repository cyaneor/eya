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
 * @brief Calculates the mathematical size of an interval.
 *
 * This macro calculates the difference between the inclusive maximum
 * and minimum values of the interval, ignoring whether the bounds
 * are open or closed for counting integers.
 *
 * @param interval_type The type of interval, one of:
 *                      - EYA_INTERVAL_TYPE_CLOSED       : [min, max]
 *                      - EYA_INTERVAL_TYPE_LEFT_OPEN    : (min, max]
 *                      - EYA_INTERVAL_TYPE_RIGHT_OPEN   : [min, max)
 *                      - EYA_INTERVAL_TYPE_OPEN         : (min, max)
 * @param min The lower bound of the interval.
 * @param max The upper bound of the interval.
 *
 * @return The difference between the inclusive max and min values.
 *         May be negative if max < min.
 *
 * @note For integer intervals, this is not the same as the number of elements.
 * @warning Arguments are evaluated multiple times - avoid expressions with side effects.
 */
#define eya_interval_size(interval_type, min, max)                                                 \
    (eya_interval_max(interval_type, max) - eya_interval_min(interval_type, min))

/**
 * @def eya_interval_cardinality(interval_type, min, max)
 * @brief Calculates the number of discrete integer values in an interval.
 *
 * This macro calculates the count of integers contained within the
 * specified interval type.
 *
 * @param interval_type The type of interval, one of:
 *                      - EYA_INTERVAL_TYPE_CLOSED       : [min, max]
 *                      - EYA_INTERVAL_TYPE_LEFT_OPEN    : (min, max]
 *                      - EYA_INTERVAL_TYPE_RIGHT_OPEN   : [min, max)
 *                      - EYA_INTERVAL_TYPE_OPEN         : (min, max)
 * @param min The lower bound of the interval.
 * @param max The upper bound of the interval.
 *
 * @return The number of integer values in the interval.
 *         Returns 0 if the interval is invalid.
 *
 * @note This is equivalent to eya_interval_size(...) + 1.
 * @warning Arguments are evaluated multiple times - avoid expressions with side effects.
 */
#define eya_interval_cardinality(interval_type, min, max)                                          \
    (eya_interval_size(interval_type, min, max) + 1)

/**
 * @def eya_interval_wrap_around_to(T, interval_type, x, r, min, max, c)
 * @brief Wraps a value around a specified interval and calculates the number of cycles.
 *
 * This macro takes a value `x` and maps it to the interval defined by `min`
 * and `max` based on the specified `interval_type`.
 *
 * It computes the wrapped value (`r`)
 * and the number of cycles (`c`) that the value wraps around the interval.
 * The macro handles edge cases such as zero-range intervals and values outside the interval.
 *
 * @param T             The data type of the values (e.g., int, long).
 * @param interval_type The type of interval (e.g., EYA_INTERVAL_TYPE_OPEN,
 *                                                  EYA_INTERVAL_TYPE_CLOSED,
 *                                                  EYA_INTERVAL_TYPE_LEFT_OPEN,
 *                                                  EYA_INTERVAL_TYPE_RIGHT_OPEN).
 * @param x            The input value to be wrapped.
 * @param r            The output wrapped value within the interval [min, max].
 * @param min          The lower bound of the interval.
 * @param max          The upper bound of the interval.
 * @param c            The output number of cycles (wraps) around the interval.
 *
 * @note The macro assumes the existence of helper functions `eya_interval_cardinality`
 *       and `eya_interval_contains_value` to compute the interval's cardinality
 *       and check if a value lies within the interval, respectively.
 *
 * @warning If the interval range (`max - min`) is zero,
 *          the macro sets `c` to 0 and `r` to `min`.
 *
 * Example usage:
 * ```c
 * int result, cycles;
 * eya_interval_wrap_around_to(int, EYA_INTERVAL_TYPE_CLOSED, 10, result, 0, 5, cycles);
 * // If x = 10, min = 0, max = 5, interval_type = EYA_INTERVAL_TYPE_CLOSED,
 * // then result = 0, cycles = 2 (since 10 wraps around [0,5] twice).
 * ```
 */
#define eya_interval_wrap_around_to(T, interval_type, x, r, min, max, c)                           \
    do                                                                                             \
    {                                                                                              \
        T _x   = (x);                                                                              \
        T _min = (min);                                                                            \
        T _max = (max);                                                                            \
        T _rng = eya_interval_cardinality(interval_type, _min, _max);                              \
                                                                                                   \
        if (_rng == 0)                                                                             \
        {                                                                                          \
            (c) = 0;                                                                               \
            (r) = _min;                                                                            \
        }                                                                                          \
        else if (eya_interval_contains_value(interval_type, _min, _x, _max))                       \
        {                                                                                          \
            (c) = 0;                                                                               \
            (r) = _x;                                                                              \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
            T _off     = _x - _min;                                                                \
            T _cycles  = _off / _rng;                                                              \
            T _wrapped = _off % _rng;                                                              \
                                                                                                   \
            if (_off < 0)                                                                          \
            {                                                                                      \
                _cycles  = (_off - _rng + 1) / _rng;                                               \
                _wrapped = _off - _cycles * _rng;                                                  \
            }                                                                                      \
                                                                                                   \
            _wrapped += _min;                                                                      \
            if (_wrapped == _min && ((interval_type) == EYA_INTERVAL_TYPE_LEFT_OPEN ||             \
                                     (interval_type) == EYA_INTERVAL_TYPE_OPEN))                   \
            {                                                                                      \
                _wrapped += _rng;                                                                  \
                _cycles--;                                                                         \
            }                                                                                      \
                                                                                                   \
            (c) = _cycles;                                                                         \
            (r) = _wrapped;                                                                        \
        }                                                                                          \
    } while (0)

/**
 * @def eya_interval_wrap_around(T, interval_type, x, min, max, cycles)
 * @brief Wraps a value around a specified interval and calculates the number of cycles.
 *
 * This macro is a simplified wrapper around `eya_interval_wrap_around_to`.
 * It takes a value `x` and maps it to the interval defined by `min`
 * and `max` based on the specified `interval_type`.
 *
 * The wrapped value is stored in `x`,
 * and the number of cycles is stored in `cycles`.
 *
 * @param T             The data type of the values (e.g., int, long).
 * @param interval_type The type of interval (e.g., EYA_INTERVAL_TYPE_OPEN,
 *                                                  EYA_INTERVAL_TYPE_CLOSED,
 *                                                  EYA_INTERVAL_TYPE_LEFT_OPEN,
 *                                                  EYA_INTERVAL_TYPE_RIGHT_OPEN).
 * @param x            The input value to be wrapped (also used to store the output wrapped value).
 * @param min          The lower bound of the interval.
 * @param max          The upper bound of the interval.
 * @param cycles       The output number of cycles (wraps) around the interval.
 *
 * @note This macro relies on `eya_interval_wrap_around_to` for its implementation.
 *       It assumes the existence of helper functions `eya_interval_cardinality`
 *       and `eya_interval_contains_value` to compute the interval's cardinality
 *       and check if a value lies within the interval, respectively.
 *
 * @warning If the interval range (`max - min`) is zero,
 *          the macro sets `cycles` to 0 and `x` to `min`.
 *
 * Example usage:
 * ```c
 * int value = 10, cycles;
 * eya_interval_wrap_around(int, EYA_INTERVAL_TYPE_CLOSED, value, 0, 5, cycles);
 * // If value = 10, min = 0, max = 5, interval_type = EYA_INTERVAL_TYPE_CLOSED,
 * // then value = 0, cycles = 2 (since 10 wraps around [0,5] twice).
 * ```
 */
#define eya_interval_wrap_around(T, interval_type, x, min, max, cycles)                            \
    eya_interval_wrap_around_to(T, interval_type, x, x, min, max, cycles)

#endif // EYA_INTERVAL_UTIL_H