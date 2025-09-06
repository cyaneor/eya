/**
 * @file numeric_clamp.h
 * @brief Macros for clamping and wrapping integer values within ranges
 *
 * This header provides utilities for constraining integer values
 * to specified intervals with different boundary inclusion modes:
 * - Closed:      [min, max]
 * - Right-open:  [min, max)
 * - Left-open:   (min, max]
 * - Open:        (min, max)
 *
 * Values outside the range are wrapped back into the interval,
 * with optional alignment from the lower or upper bound.
 * The number of wrap cycles is tracked via an overflow parameter.
 */

#ifndef EYA_NUMERIC_CLAMP_H
#define EYA_NUMERIC_CLAMP_H

/**
 * @def eya_numeric_clamp(T, val, min, max, overflow, adjust, shift, use_lower, use_upper,
 * align_mode)
 * @brief Core macro for clamping/wrapping values into a range
 *
 * @param T          Integral type of the values
 * @param val        Value to clamp (modified in place)
 * @param min        Range lower bound
 * @param max        Range upper bound
 * @param overflow   Output: number of completed wrap cycles
 * @param adjust     Range adjustment (+1, 0, -1) for open/closed interval handling
 * @param shift      Additional shift applied before normalization
 * @param use_lower  Lower bound inclusivity flag (1 = inclusive, 0 = exclusive)
 * @param use_upper  Upper bound inclusivity flag (1 = inclusive, 0 = exclusive)
 * @param align_mode Alignment mode:
 *                   - 0 = align from lower bound
 *                   - 1 = align from upper bound
 */
#define eya_numeric_clamp(                                                                         \
    T, val, min, max, overflow, adjust, shift, use_lower, use_upper, align_mode)                   \
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
            if (align_mode)                                                                        \
                (val) = _hi - _off;                                                                \
            else                                                                                   \
                (val) = _off + _lo;                                                                \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
            (overflow) = 0;                                                                        \
        }                                                                                          \
    } while (0)

/**
 * @def eya_numeric_clamp_closed(T, val, min, max, overflow, align_mode)
 * @brief Clamp/wrap into closed interval [min, max]
 *
 * @param T          Integral type
 * @param val        Value to clamp (modified in place)
 * @param min        Lower bound (inclusive)
 * @param max        Upper bound (inclusive)
 * @param overflow   Output: number of wrap cycles
 * @param align_mode Alignment mode:
 *                   - 0 = from lower bound
 *                   - 1 = from upper bound
 */
#define eya_numeric_clamp_closed(T, val, min, max, overflow, align_mode)                           \
    eya_numeric_clamp(T, val, min, max, overflow, +1, 0, 1, 1, align_mode)

/**
 * @def eya_numeric_clamp_ropen(T, val, min, max, overflow, align_mode)
 * @brief Clamp/wrap into right-open interval [min, max)
 *
 * @param T          Integral type
 * @param val        Value to clamp (modified in place)
 * @param min        Lower bound (inclusive)
 * @param max        Upper bound (exclusive)
 * @param overflow   Output: number of wrap cycles
 * @param align_mode Alignment mode:
 *                   - 0 = from lower bound
 *                   - 1 = from upper bound
 */
#define eya_numeric_clamp_ropen(T, val, min, max, overflow, align_mode)                            \
    eya_numeric_clamp(T, val, min, max, overflow, 0, 0, 1, 0, align_mode)

/**
 * @def eya_numeric_clamp_lopen(T, val, min, max, overflow, align_mode)
 * @brief Clamp/wrap into left-open interval (min, max]
 *
 * @param T          Integral type
 * @param val        Value to clamp (modified in place)
 * @param min        Lower bound (exclusive)
 * @param max        Upper bound (inclusive)
 * @param overflow   Output: number of wrap cycles
 * @param align_mode Alignment mode:
 *                   - 0 = from lower bound
 *                   - 1 = from upper bound
 */
#define eya_numeric_clamp_lopen(T, val, min, max, overflow, align_mode)                            \
    eya_numeric_clamp(T, val, min, max, overflow, 0, -1, 0, 1, align_mode)

/**
 * @def eya_numeric_clamp_open(T, val, min, max, overflow, align_mode)
 * @brief Clamp/wrap into open interval (min, max)
 *
 * @param T          Integral type
 * @param val        Value to clamp (modified in place)
 * @param min        Lower bound (exclusive)
 * @param max        Upper bound (exclusive)
 * @param overflow   Output: number of wrap cycles
 * @param align_mode Alignment mode:
 *                   - 0 = from lower bound
 *                   - 1 = from upper bound
 */
#define eya_numeric_clamp_open(T, val, min, max, overflow, align_mode)                             \
    eya_numeric_clamp(T, val, min, max, overflow, -1, -1, 0, 0, align_mode)

#endif // EYA_NUMERIC_CLAMP_H
