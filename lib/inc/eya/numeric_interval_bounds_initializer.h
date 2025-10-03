/**
 * @file numeric_interval_bounds_initializer.h
 * @brief Macros for initializing interval bounds for numeric types.
 *
 * This header provides macros for initializing interval bounds structures
 * for various numeric type aliases defined in @ref numeric_types.h.
 *
 * Each macro initializes an interval bounds structure with the minimum
 * and maximum values of the corresponding numeric type, as determined
 * by the macros in @ref numeric_limit.h.
 *
 * The macros defined in this file are intended to simplify the creation
 * of interval bounds objects by automatically setting their `lower` and
 * `upper` fields to the minimum and maximum values of the respective
 * numeric types.
 *
 * Supported numeric types:
 * - `eya_uchar_t` (unsigned char)
 * - `eya_ushort_t` (unsigned short)
 * - `eya_uint_t` (unsigned int)
 * - `eya_ulong_t` (unsigned long)
 * - `eya_ullong_t` (unsigned long long)
 * - `eya_schar_t` (signed char)
 * - `eya_sshort_t` (signed short)
 * - `eya_sint_t` (signed int)
 * - `eya_slong_t` (signed long)
 * - `eya_sllong_t` (signed long long)
 *
 * Example usage:
 * @code
 * #include <eya/numeric_interval_bounds_initializer.h>
 *
 * // Initialize an interval bounds structure for unsigned int
 * eya_uint_interval_bounds range = eya_uint_interval_bounds_initializer;
 * // range.lower is set to the minimum value of eya_uint_t (0)
 * // range.upper is set to the maximum value of eya_uint_t (e.g., UINT_MAX)
 *
 * if (value >= range.lower && value <= range.upper) {
 *     // value is within the interval
 * }
 * @endcode
 *
 * @see numeric_types.h
 * @see numeric_limit.h
 * @see initializer.h
 * @see numeric_interval_bounds_types.h
 */

#ifndef EYA_NUMERIC_INTERVAL_BOUNDS_INITIALIZER_H
#define EYA_NUMERIC_INTERVAL_BOUNDS_INITIALIZER_H

#include <eya/initializer.h>
#include <eya/numeric_types.h>
#include <eya/numeric_limit.h>

/**
 * @def eya_uchar_interval_bounds_initializer
 * @brief Initializes an interval bounds structure for `eya_uchar_t`.
 * @details Creates an `eya_uchar_interval_bounds` structure with `lower` set to
 *          the minimum value of `eya_uchar_t` and `upper` set to the maximum value
 *          of `eya_uchar_t`, as defined by @ref eya_numeric_limit_min and
 *          @ref eya_numeric_limit_max.
 *
 * @return An initialized `eya_uchar_interval_bounds` structure.
 */
#define eya_uchar_interval_bounds_initializer                                                      \
    eya_initializer(eya_numeric_limit_min(eya_uchar_t), eya_numeric_limit_max(eya_uchar_t))

/**
 * @def eya_ushort_interval_bounds_initializer
 * @brief Initializes an interval bounds structure for `eya_ushort_t`.
 * @details Creates an `eya_ushort_interval_bounds` structure with `lower` set to
 *          the minimum value of `eya_ushort_t` and `upper` set to the maximum value
 *          of `eya_ushort_t`, as defined by @ref eya_numeric_limit_min and
 *          @ref eya_numeric_limit_max.
 *
 * @return An initialized `eya_ushort_interval_bounds` structure.
 */
#define eya_ushort_interval_bounds_initializer                                                     \
    eya_initializer(eya_numeric_limit_min(eya_ushort_t), eya_numeric_limit_max(eya_ushort_t))

/**
 * @def eya_uint_interval_bounds_initializer
 * @brief Initializes an interval bounds structure for `eya_uint_t`.
 * @details Creates an `eya_uint_interval_bounds` structure with `lower` set to
 *          the minimum value of `eya_uint_t` and `upper` set to the maximum value
 *          of `eya_uint_t`, as defined by @ref eya_numeric_limit_min and
 *          @ref eya_numeric_limit_max.
 *
 * @return An initialized `eya_uint_interval_bounds` structure.
 */
#define eya_uint_interval_bounds_initializer                                                       \
    eya_initializer(eya_numeric_limit_min(eya_uint_t), eya_numeric_limit_max(eya_uint_t))

/**
 * @def eya_ulong_interval_bounds_initializer
 * @brief Initializes an interval bounds structure for `eya_ulong_t`.
 * @details Creates an `eya_ulong_interval_bounds` structure with `lower` set to
 *          the minimum value of `eya_ulong_t` and `upper` set to the maximum value
 *          of `eya_ulong_t`, as defined by @ref eya_numeric_limit_min and
 *          @ref eya_numeric_limit_max.
 *
 * @return An initialized `eya_ulong_interval_bounds` structure.
 */
#define eya_ulong_interval_bounds_initializer                                                      \
    eya_initializer(eya_numeric_limit_min(eya_ulong_t), eya_numeric_limit_max(eya_ulong_t))

/**
 * @def eya_ullong_interval_bounds_initializer
 * @brief Initializes an interval bounds structure for `eya_ullong_t`.
 * @details Creates an `eya_ullong_interval_bounds` structure with `lower` set to
 *          the minimum value of `eya_ullong_t` and `upper` set to the maximum value
 *          of `eya_ullong_t`, as defined by @ref eya_numeric_limit_min and
 *          @ref eya_numeric_limit_max.
 *
 * @return An initialized `eya_ullong_interval_bounds` structure.
 */
#define eya_ullong_interval_bounds_initializer                                                     \
    eya_initializer(eya_numeric_limit_min(eya_ullong_t), eya_numeric_limit_max(eya_ullong_t))

/**
 * @def eya_schar_interval_bounds_initializer
 * @brief Initializes an interval bounds structure for `eya_schar_t`.
 * @details Creates an `eya_schar_interval_bounds` structure with `lower` set to
 *          the minimum value of `eya_schar_t` and `upper` set to the maximum value
 *          of `eya_schar_t`, as defined by @ref eya_numeric_limit_min and
 *          @ref eya_numeric_limit_max.
 *
 * @return An initialized `eya_schar_interval_bounds` structure.
 */
#define eya_schar_interval_bounds_initializer                                                      \
    eya_initializer(eya_numeric_limit_min(eya_schar_t), eya_numeric_limit_max(eya_schar_t))

/**
 * @def eya_sshort_interval_bounds_initializer
 * @brief Initializes an interval bounds structure for `eya_sshort_t`.
 * @details Creates an `eya_sshort_interval_bounds` structure with `lower` set to
 *          the minimum value of `eya_sshort_t` and `upper` set to the maximum value
 *          of `eya_sshort_t`, as defined by @ref eya_numeric_limit_min and
 *          @ref eya_numeric_limit_max.
 *
 * @return An initialized `eya_sshort_interval_bounds` structure.
 */
#define eya_sshort_interval_bounds_initializer                                                     \
    eya_initializer(eya_numeric_limit_min(eya_sshort_t), eya_numeric_limit_max(eya_sshort_t))

/**
 * @def eya_sint_interval_bounds_initializer
 * @brief Initializes an interval bounds structure for `eya_sint_t`.
 * @details Creates an `eya_sint_interval_bounds` structure with `lower` set to
 *          the minimum value of `eya_sint_t` and `upper` set to the maximum value
 *          of `eya_sint_t`, as defined by @ref eya_numeric_limit_min and
 *          @ref eya_numeric_limit_max.
 *
 * @return An initialized `eya_sint_interval_bounds` structure.
 */
#define eya_sint_interval_bounds_initializer                                                       \
    eya_initializer(eya_numeric_limit_min(eya_sint_t), eya_numeric_limit_max(eya_sint_t))

/**
 * @def eya_slong_interval_bounds_initializer
 * @brief Initializes an interval bounds structure for `eya_slong_t`.
 * @details Creates an `eya_slong_interval_bounds` structure with `lower` set to
 *          the minimum value of `eya_slong_t` and `upper` set to the maximum value
 *          of `eya_slong_t`, as defined by @ref eya_numeric_limit_min and
 *          @ref eya_numeric_limit_max.
 *
 * @return An initialized `eya_slong_interval_bounds` structure.
 */
#define eya_slong_interval_bounds_initializer                                                      \
    eya_initializer(eya_numeric_limit_min(eya_slong_t), eya_numeric_limit_max(eya_slong_t))

/**
 * @def eya_sllong_interval_bounds_initializer
 * @brief Initializes an interval bounds structure for `eya_sllong_t`.
 * @details Creates an `eya_sllong_interval_bounds` structure with `lower` set to
 *          the minimum value of `eya_sllong_t` and `upper` set to the maximum value
 *          of `eya_sllong_t`, as defined by @ref eya_numeric_limit_min and
 *          @ref eya_numeric_limit_max.
 *
 * @return An initialized `eya_sllong_interval_bounds` structure.
 */
#define eya_sllong_interval_bounds_initializer                                                     \
    eya_initializer(eya_numeric_limit_min(eya_sllong_t), eya_numeric_limit_max(eya_sllong_t))

#endif // EYA_NUMERIC_INTERVAL_BOUNDS_INITIALIZER_H