/**
 * @file numeric_clamp.h
 * @brief Value clamping and range wrapping utilities for integral types
 *
 * Provides macros for clamping values to specified ranges with various
 * boundary inclusion behaviors. Supports both clamping and wrapping
 * with overflow tracking.
 */

#ifndef EYA_NUMERIC_CLAMP_H
#define EYA_NUMERIC_CLAMP_H

/**
 * @def eya_numeric_clamp(T, val, min, max, overflow, adjust, shift, use_lower, use_upper)
 * @brief Internal macro for clamping/wrapping values into specified ranges
 *
 * @param T          Integral type of the values
 * @param val        Value to clamp (modified in place)
 * @param min        Lower bound of the range
 * @param max        Upper bound of the range
 * @param overflow   Output parameter for number of wrap cycles
 * @param adjust     Adjustment to range size (0, ±1) for open/closed intervals
 * @param shift      Extra shift for normalizing values outside bounds
 * @param use_lower  Whether lower bound is inclusive (1) or exclusive (0)
 * @param use_upper  Whether upper bound is inclusive (1) or exclusive (0)
 */
#define eya_numeric_clamp(T, val, min, max, overflow, adjust, shift, use_lower, use_upper)         \
    do                                                                                             \
    {                                                                                              \
        T _range = (max) - (min) + (adjust);                                                       \
        if (_range <= 0)                                                                           \
            _range = 1;                                                                            \
                                                                                                   \
        T _lo = (min) + !(use_lower);                                                              \
        T _hi = (max) - !(use_upper);                                                              \
                                                                                                   \
        if ((val) < _lo || (val) > _hi)                                                            \
        {                                                                                          \
            T _off     = (val) - (min) + (shift);                                                  \
            (overflow) = _off / _range;                                                            \
                                                                                                   \
            if ((_off % _range) && (val) < _lo)                                                    \
                (overflow)--;                                                                      \
                                                                                                   \
            _off %= _range;                                                                        \
            if (_off < 0)                                                                          \
                _off += _range;                                                                    \
                                                                                                   \
            (val) = _off + _lo;                                                                    \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
            (overflow) = 0;                                                                        \
        }                                                                                          \
    } while (0)

/**
 * @def eya_numeric_clamp_closed(T, val, min, max, overflow)
 * @brief Clamp value to inclusive range [min, max]
 *
 * @param T        Integral type
 * @param val      Value to clamp (modified in place)
 * @param min      Lower bound (inclusive)
 * @param max      Upper bound (inclusive)
 * @param overflow Output: number of wrap cycles
 */
#define eya_numeric_clamp_closed(T, val, min, max, overflow)                                       \
    eya_numeric_clamp(T, val, min, max, overflow, +1, 0, 1, 1)

/**
 * @def eya_numeric_clamp_ropen(T, val, min, max, overflow)
 * @brief Clamp value to right-open range [min, max)
 *
 * @param T        Integral type
 * @param val      Value to clamp (modified in place)
 * @param min      Lower bound (inclusive)
 * @param max      Upper bound (exclusive)
 * @param overflow Output: number of wrap cycles
 */
#define eya_numeric_clamp_ropen(T, val, min, max, overflow)                                        \
    eya_numeric_clamp(T, val, min, max, overflow, 0, 0, 1, 0)

/**
 * @def eya_numeric_clamp_lopen(T, val, min, max, overflow)
 * @brief Clamp value to left-open range (min, max]
 *
 * @param T        Integral type
 * @param val      Value to clamp (modified in place)
 * @param min      Lower bound (exclusive)
 * @param max      Upper bound (inclusive)
 * @param overflow Output: number of wrap cycles
 */
#define eya_numeric_clamp_lopen(T, val, min, max, overflow)                                        \
    eya_numeric_clamp(T, val, min, max, overflow, 0, -1, 0, 1)

/**
 * @def eya_numeric_clamp_open(T, val, min, max, overflow)
 * @brief Clamp value to open range (min, max)
 *
 * @param T        Integral type
 * @param val      Value to clamp (modified in place)
 * @param min      Lower bound (exclusive)
 * @param max      Upper bound (exclusive)
 * @param overflow Output: number of wrap cycles
 */
#define eya_numeric_clamp_open(T, val, min, max, overflow)                                         \
    eya_numeric_clamp(T, val, min, max, overflow, -1, -1, 0, 0)

#endif // EYA_NUMERIC_CLAMP_H