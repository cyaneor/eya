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

/**
 * @def eya_interval_closed_add(T, self, val, min, max, overflow)
 * @brief Adds a value to a variable within a closed interval [min, max].
 * @param T Data type of the variable
 * @param self Variable to modify (passed by reference)
 * @param val Value to add
 * @param min Minimum value of the interval
 * @param max Maximum value of the interval
 * @param overflow Output parameter for overflow count
 */
#define eya_interval_closed_add(T, self, val, min, max, overflow)                                  \
    do                                                                                             \
    {                                                                                              \
        T cur_abs = self - min;                                                                    \
        T sum_abs = cur_abs + val;                                                                 \
        T range   = max - min + 1;                                                                 \
        T new_abs = sum_abs % range;                                                               \
        overflow  = sum_abs / range;                                                               \
        self      = (new_abs < 0) ? (new_abs + range + min) : (new_abs + min);                     \
    } while (0)

/**
 * @def eya_interval_ropen_add(T, self, val, min, max, overflow)
 * @brief Adds a value to a variable within a right-open interval [min, max).
 * @param T Data type of the variable
 * @param self Variable to modify (passed by reference)
 * @param val Value to add
 * @param min Minimum value of the interval
 * @param max Maximum value of the interval (exclusive)
 * @param overflow Output parameter for overflow count
 */
#define eya_interval_ropen_add(T, self, val, min, max, overflow)                                   \
    do                                                                                             \
    {                                                                                              \
        T cur_abs = self - min;                                                                    \
        T sum_abs = cur_abs + val;                                                                 \
        T range   = max - min;                                                                     \
        T new_abs = sum_abs % range;                                                               \
        overflow  = sum_abs / range;                                                               \
        self      = (new_abs < 0) ? (new_abs + range + min) : (new_abs + min);                     \
    } while (0)

/**
 * @def eya_interval_lopen_add(T, self, val, min, max, overflow)
 * @brief Adds a value to a variable within a left-open interval (min, max].
 * @param T Data type of the variable
 * @param self Variable to modify (passed by reference)
 * @param val Value to add
 * @param min Minimum value of the interval (exclusive)
 * @param max Maximum value of the interval
 * @param overflow Output parameter for overflow count
 */
#define eya_interval_lopen_add(T, self, val, min, max, overflow)                                   \
    do                                                                                             \
    {                                                                                              \
        T cur_abs = self - min;                                                                    \
        T sum_abs = cur_abs + val;                                                                 \
        T range   = max - min;                                                                     \
        T new_abs = sum_abs % range;                                                               \
        overflow  = sum_abs / range;                                                               \
        self      = (new_abs <= 0) ? (new_abs + range + min) : (new_abs + min);                    \
    } while (0)

/**
 * @def eya_interval_open_add(T, self, val, min, max, overflow)
 * @brief Adds a value to a variable within an open interval (min, max).
 * @param T Data type of the variable
 * @param self Variable to modify (passed by reference)
 * @param val Value to add
 * @param min Minimum value of the interval (exclusive)
 * @param max Maximum value of the interval (exclusive)
 * @param overflow Output parameter for overflow count
 */
#define eya_interval_open_add(T, self, val, min, max, overflow)                                    \
    do                                                                                             \
    {                                                                                              \
        T range     = (max) - (min)-1;                                                             \
        T cur_abs   = (self) - (min)-1;                                                            \
        T total_abs = (T)(cur_abs + (val));                                                        \
        T new_abs   = total_abs % range;                                                           \
        overflow    = total_abs / range;                                                           \
        if (new_abs < 0)                                                                           \
        {                                                                                          \
            new_abs += range;                                                                      \
            overflow -= 1;                                                                         \
        }                                                                                          \
        (self) = new_abs + (min) + 1;                                                              \
    } while (0)

/**
 * @def eya_interval_closed_sub(T, self, val, min, max, overflow)
 * @brief Subtracts a value from a variable within a closed interval [min, max].
 * @param T Data type of the variable
 * @param self Variable to modify (passed by reference)
 * @param val Value to subtract
 * @param min Minimum value of the interval
 * @param max Maximum value of the interval
 * @param overflow Output parameter for overflow count
 */
#define eya_interval_closed_sub(T, self, val, min, max, overflow)                                  \
    do                                                                                             \
    {                                                                                              \
        T range        = max - min + 1;                                                            \
        T total_change = val;                                                                      \
        T current_pos  = self - min;                                                               \
        T new_pos      = current_pos - total_change;                                               \
        overflow       = 0;                                                                        \
                                                                                                   \
        if (new_pos < 0)                                                                           \
        {                                                                                          \
            overflow = (-new_pos - 1) / range + 1;                                                 \
            new_pos  = range - (-new_pos - 1) % range - 1;                                         \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
            overflow = new_pos / range;                                                            \
            new_pos  = new_pos % range;                                                            \
        }                                                                                          \
                                                                                                   \
        self = new_pos + min;                                                                      \
    } while (0)

/**
 * @def eya_interval_ropen_sub(T, self, val, min, max, overflow)
 * @brief Subtracts a value from a variable within a right-open interval [min, max).
 * @param T Data type of the variable
 * @param self Variable to modify (passed by reference)
 * @param val Value to subtract
 * @param min Minimum value of the interval
 * @param max Maximum value of the interval (exclusive)
 * @param overflow Output parameter for overflow count
 */
#define eya_interval_ropen_sub(T, self, val, min, max, overflow)                                   \
    do                                                                                             \
    {                                                                                              \
        T range        = max - min;                                                                \
        T total_change = val;                                                                      \
        T current_pos  = self - min;                                                               \
        T new_pos      = current_pos - total_change;                                               \
        overflow       = 0;                                                                        \
                                                                                                   \
        if (new_pos < 0)                                                                           \
        {                                                                                          \
            overflow = (-new_pos - 1) / range + 1;                                                 \
            new_pos  = range - (-new_pos - 1) % range - 1;                                         \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
            overflow = new_pos / range;                                                            \
            new_pos  = new_pos % range;                                                            \
        }                                                                                          \
                                                                                                   \
        self = new_pos + min;                                                                      \
    } while (0)

/**
 * @def eya_interval_lopen_sub(T, self, val, min, max, overflow)
 * @brief Subtracts a value from a variable within a left-open interval (min, max].
 * @param T Data type of the variable
 * @param self Variable to modify (passed by reference)
 * @param val Value to subtract
 * @param min Minimum value of the interval (exclusive)
 * @param max Maximum value of the interval
 * @param overflow Output parameter for overflow count
 */
#define eya_interval_lopen_sub(T, self, val, min, max, overflow)                                   \
    do                                                                                             \
    {                                                                                              \
        T range        = max - min;                                                                \
        T total_change = val;                                                                      \
        T current_pos  = self - min - 1;                                                           \
        T new_pos      = current_pos - total_change;                                               \
        overflow       = 0;                                                                        \
                                                                                                   \
        if (new_pos < 0)                                                                           \
        {                                                                                          \
            overflow = (-new_pos - 1) / range + 1;                                                 \
            new_pos  = range - (-new_pos - 1) % range - 1;                                         \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
            overflow = new_pos / range;                                                            \
            new_pos  = new_pos % range;                                                            \
        }                                                                                          \
                                                                                                   \
        self = new_pos + min + 1;                                                                  \
    } while (0)

/**
 * @def eya_interval_open_sub(T, self, val, min, max, overflow)
 * @brief Subtracts a value from a variable within an open interval (min, max).
 * @param T Data type of the variable
 * @param self Variable to modify (passed by reference)
 * @param val Value to subtract
 * @param min Minimum value of the interval (exclusive)
 * @param max Maximum value of the interval (exclusive)
 * @param overflow Output parameter for overflow count
 */
#define eya_interval_open_sub(T, self, val, min, max, overflow)                                    \
    do                                                                                             \
    {                                                                                              \
        T range     = max - min - 1;                                                               \
        T cur_pos   = self - min;                                                                  \
        T total_sub = cur_pos - val;                                                               \
        overflow    = (total_sub < 0) ? (total_sub - range + 1) / range : 0;                       \
        if (overflow < 0)                                                                          \
        {                                                                                          \
            total_sub -= overflow * range;                                                         \
            overflow = -overflow;                                                                  \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
            overflow = 0;                                                                          \
        }                                                                                          \
        T new_pos = total_sub % range;                                                             \
        if (new_pos < 0)                                                                           \
        {                                                                                          \
            new_pos += range;                                                                      \
        }                                                                                          \
        self = new_pos + min;                                                                      \
    } while (0)

/**
 * @def eya_interval_closed_mul(T, self, val, min, max, overflow)
 * @brief Multiplies a variable by a value within a closed interval [min, max].
 * @param T Data type of the variable
 * @param self Variable to modify (passed by reference)
 * @param val Value to multiply by
 * @param min Minimum value of the interval
 * @param max Maximum value of the interval
 * @param overflow Output parameter for overflow count
 */
#define eya_interval_closed_mul(T, self, val, min, max, overflow)                                  \
    do                                                                                             \
    {                                                                                              \
        T result = self * val;                                                                     \
        T range  = max - min + 1;                                                                  \
                                                                                                   \
        if (result >= min && result <= max)                                                        \
        {                                                                                          \
            self     = result;                                                                     \
            overflow = 0;                                                                          \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
            T normalized = (result - min) % range;                                                 \
            if (normalized < 0)                                                                    \
                normalized += range;                                                               \
            self     = normalized + min;                                                           \
            overflow = (result - min) / range;                                                     \
            if (result < min)                                                                      \
                overflow--;                                                                        \
        }                                                                                          \
    } while (0)

/**
 * @def eya_interval_ropen_mul(T, self, val, min, max, overflow)
 * @brief Multiplies a variable by a value within a right-open interval [min, max).
 * @param T Data type of the variable
 * @param self Variable to modify (passed by reference)
 * @param val Value to multiply by
 * @param min Minimum value of the interval
 * @param max Maximum value of the interval (exclusive)
 * @param overflow Output parameter for overflow count
 */
#define eya_interval_ropen_mul(T, self, val, min, max, overflow)                                   \
    do                                                                                             \
    {                                                                                              \
        T result = self * val;                                                                     \
        T range  = max - min;                                                                      \
        T offset = result - min;                                                                   \
                                                                                                   \
        if (offset >= 0)                                                                           \
        {                                                                                          \
            overflow = offset / range;                                                             \
            offset   = offset % range;                                                             \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
            overflow = (offset - range + 1) / range;                                               \
            offset   = offset % range;                                                             \
            if (offset < 0)                                                                        \
                offset += range;                                                                   \
        }                                                                                          \
                                                                                                   \
        self = offset + min;                                                                       \
    } while (0)

/**
 * @def eya_interval_lopen_mul(T, self, val, min, max, overflow)
 * @brief Multiplies a variable by a value within a left-open interval (min, max].
 * @param T Data type of the variable
 * @param self Variable to modify (passed by reference)
 * @param val Value to multiply by
 * @param min Minimum value of the interval (exclusive)
 * @param max Maximum value of the interval
 * @param overflow Output parameter for overflow count
 */
#define eya_interval_lopen_mul(T, self, val, min, max, overflow)                                   \
    do                                                                                             \
    {                                                                                              \
        T prod  = self * val;                                                                      \
        T range = max - min;                                                                       \
        if (prod > max || prod <= min)                                                             \
        {                                                                                          \
            T prod_abs = prod - min;                                                               \
            T new_abs  = prod_abs % range;                                                         \
            overflow   = prod_abs / range;                                                         \
            self       = (new_abs <= 0) ? (new_abs + range + min) : (new_abs + min);               \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
            overflow = 0;                                                                          \
            self     = prod;                                                                       \
        }                                                                                          \
    } while (0)

/**
 * @def eya_interval_open_mul(T, self, val, min, max, overflow)
 * @brief Multiplies a variable by a value within an open interval (min, max).
 * @param T Data type of the variable
 * @param self Variable to modify (passed by reference)
 * @param val Value to multiply by
 * @param min Minimum value of the interval (exclusive)
 * @param max Maximum value of the interval (exclusive)
 * @param overflow Output parameter for overflow count
 */
#define eya_interval_open_mul(T, self, val, min, max, overflow)                                    \
    do                                                                                             \
    {                                                                                              \
        T prod  = self * val;                                                                      \
        T range = max - min - 1;                                                                   \
        if (prod <= min)                                                                           \
        {                                                                                          \
            overflow = (min - prod + range - 1) / range;                                           \
            self     = prod + range * overflow;                                                    \
        }                                                                                          \
        else if (prod >= max)                                                                      \
        {                                                                                          \
            overflow = (prod - max + range - 1) / range;                                           \
            self     = prod - range * overflow;                                                    \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
            overflow = 0;                                                                          \
            self     = prod;                                                                       \
        }                                                                                          \
    } while (0)

/**
 * @def eya_interval_closed_div(T, self, val, min, max, overflow)
 * @brief Divides a variable by a value within a closed interval [min, max].
 * @param T Data type of the variable
 * @param self Variable to modify (passed by reference)
 * @param val Value to divide by
 * @param min Minimum value of the interval
 * @param max Maximum value of the interval
 * @param overflow Output parameter for overflow count
 */
#define eya_interval_closed_div(T, self, val, min, max, overflow)                                  \
    do                                                                                             \
    {                                                                                              \
        T cur_abs  = self - min;                                                                   \
        T quot_abs = (val != 0) ? cur_abs / val : cur_abs;                                         \
        T range    = max - min + 1;                                                                \
        T new_abs  = quot_abs % range;                                                             \
        overflow   = quot_abs / range;                                                             \
        self       = (new_abs < 0) ? (new_abs + range + min) : (new_abs + min);                    \
    } while (0)

/**
 * @def eya_interval_ropen_div(T, self, val, min, max, overflow)
 * @brief Divides a variable by a value within a right-open interval [min, max).
 * @param T Data type of the variable
 * @param self Variable to modify (passed by reference)
 * @param val Value to divide by
 * @param min Minimum value of the interval
 * @param max Maximum value of the interval (exclusive)
 * @param overflow Output parameter for overflow count
 */
#define eya_interval_ropen_div(T, self, val, min, max, overflow)                                   \
    do                                                                                             \
    {                                                                                              \
        T cur_abs  = self - min;                                                                   \
        T quot_abs = (val != 0) ? cur_abs / val : cur_abs;                                         \
        T range    = max - min;                                                                    \
        T new_abs  = quot_abs % range;                                                             \
        overflow   = quot_abs / range;                                                             \
        self       = (new_abs < 0) ? (new_abs + range + min) : (new_abs + min);                    \
    } while (0)

/**
 * @def eya_interval_lopen_div(T, self, val, min, max, overflow)
 * @brief Divides a variable by a value within a left-open interval (min, max].
 * @param T Data type of the variable
 * @param self Variable to modify (passed by reference)
 * @param val Value to divide by
 * @param min Minimum value of the interval (exclusive)
 * @param max Maximum value of the interval
 * @param overflow Output parameter for overflow count
 */
#define eya_interval_lopen_div(T, self, val, min, max, overflow)                                   \
    do                                                                                             \
    {                                                                                              \
        T cur_abs  = self - min;                                                                   \
        T quot_abs = (val != 0) ? cur_abs / val : cur_abs;                                         \
        T range    = max - min;                                                                    \
        T new_abs  = quot_abs % range;                                                             \
        overflow   = quot_abs / range;                                                             \
        self       = (new_abs <= 0) ? (new_abs + range + min) : (new_abs + min);                   \
    } while (0)

/**
 * @def eya_interval_open_div(T, self, val, min, max, overflow)
 * @brief Divides a variable by a value within an open interval (min, max).
 * @param T Data type of the variable
 * @param self Variable to modify (passed by reference)
 * @param val Value to divide by
 * @param min Minimum value of the interval (exclusive)
 * @param max Maximum value of the interval (exclusive)
 * @param overflow Output parameter for overflow count
 */
#define eya_interval_open_div(T, self, val, min, max, overflow)                                    \
    do                                                                                             \
    {                                                                                              \
        T cur_abs  = self - min;                                                                   \
        T quot_abs = (val != 0) ? cur_abs / val : cur_abs;                                         \
        T range    = max - min - 1;                                                                \
        T new_abs  = quot_abs % range;                                                             \
        overflow   = quot_abs / range;                                                             \
        self       = (new_abs <= 0) ? (new_abs + range + min) : (new_abs + min);                   \
    } while (0)

#endif // EYA_INTERVAL_UTIL_H