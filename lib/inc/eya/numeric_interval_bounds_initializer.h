/**
 * @file numeric_interval_bounds_initializer.h
 * @brief Macros for initializing interval bounds for numeric types.
 *
 * This header defines macros to initialize interval bounds structures for numeric type aliases
 * defined in @ref numeric_types.h. These macros simplify the creation of interval bounds
 * objects by setting their `lower` and `upper` fields to the minimum and maximum values
 * of the respective numeric types, as provided by @ref numeric_limit.h.
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
 * // range.lower is set to 0 (minimum value of eya_uint_t)
 * // range.upper is set to UINT_MAX (maximum value of eya_uint_t)
 *
 * if (value >= range.lower && value <= range.upper) {
 *     // Value is within the valid interval for eya_uint_t
 * }
 * @endcode
 *
 * @see numeric_types.h
 * @see numeric_limit.h
 * @see initializer.h
 */

#ifndef EYA_NUMERIC_INTERVAL_BOUNDS_INITIALIZER_H
#define EYA_NUMERIC_INTERVAL_BOUNDS_INITIALIZER_H

#include <eya/initializer.h>
#include <eya/numeric_types.h>
#include <eya/numeric_limit.h>

/**
 * @def eya_numeric_interval_bounds_initializer(lower, upper, ...)
 * @brief Generic macro to initialize an interval bounds structure
 *        with specified lower and upper bounds.
 *
 * @param lower The lower bound value for the interval.
 * @param upper The upper bound value for the interval.
 * @param ... Additional arguments passed to the `eya_initializer` macro (if any).
 * @details This macro wraps the `eya_initializer` macro
 *          to create an interval bounds structure with the specified `lower` and `upper` values.
 *          It is used as a building block for type-specific initializer macros.
 *
 * @return An initialized interval bounds structure.
 */
#define eya_numeric_interval_bounds_initializer(lower, upper, ...)                                 \
    eya_initializer(lower, upper, __VA_ARGS__)

/**
 * @def eya_numeric_interval_bounds_initializer_by_type(T)
 * @brief Generic macro to initialize an interval bounds structure for a given numeric type.
 * @param T The numeric type (e.g., `eya_uint_t`, `eya_schar_t`) for which to initialize bounds.
 * @details This macro uses `eya_numeric_limit_min` and `eya_numeric_limit_max` to set
 *          the `lower` and `upper` fields of the interval bounds structure
 *          for the specified type `T`.
 *
 * @return An initialized interval bounds structure for the specified type.
 */
#define eya_numeric_interval_bounds_initializer_by_type(T)                                         \
    eya_numeric_interval_bounds_initializer(eya_numeric_limit_min(T), eya_numeric_limit_max(T))

/**
 * @def eya_uchar_interval_bounds_initializer
 * @brief Initializes an interval bounds structure for `eya_uchar_t`.
 * @details Creates an `eya_uchar_interval_bounds` structure with `lower` set to the minimum
 *          value of `eya_uchar_t` (0) and `upper` set to the maximum value of `eya_uchar_t`
 *          (e.g., UCHAR_MAX), as defined by @ref eya_numeric_limit_min and
 *          @ref eya_numeric_limit_max.
 *
 * @return An initialized `eya_uchar_interval_bounds` structure.
 */
#define eya_uchar_interval_bounds_initializer                                                      \
    eya_numeric_interval_bounds_initializer_by_type(eya_uchar_t)

/**
 * @def eya_ushort_interval_bounds_initializer
 * @brief Initializes an interval bounds structure for `eya_ushort_t`.
 * @details Creates an `eya_ushort_interval_bounds` structure with `lower` set to the minimum
 *          value of `eya_ushort_t` (0) and `upper` set to the maximum value of `eya_ushort_t`
 *          (e.g., USHRT_MAX), as defined by @ref eya_numeric_limit_min and
 *          @ref eya_numeric_limit_max.
 *
 * @return An initialized `eya_ushort_interval_bounds` structure.
 */
#define eya_ushort_interval_bounds_initializer                                                     \
    eya_numeric_interval_bounds_initializer_by_type(eya_ushort_t)

/**
 * @def eya_uint_interval_bounds_initializer
 * @brief Initializes an interval bounds structure for `eya_uint_t`.
 * @details Creates an `eya_uint_interval_bounds` structure with `lower` set to the minimum
 *          value of `eya_uint_t` (0) and `upper` set to the maximum value of `eya_uint_t`
 *          (e.g., UINT_MAX), as defined by @ref eya_numeric_limit_min and
 *          @ref eya_numeric_limit_max.
 *
 * @return An initialized `eya_uint_interval_bounds` structure.
 */
#define eya_uint_interval_bounds_initializer                                                       \
    eya_numeric_interval_bounds_initializer_by_type(eya_uint_t)

/**
 * @def eya_ulong_interval_bounds_initializer
 * @brief Initializes an interval bounds structure for `eya_ulong_t`.
 * @details Creates an `eya_ulong_interval_bounds` structure with `lower` set to the minimum
 *          value of `eya_ulong_t` (0) and `upper` set to the maximum value of `eya_ulong_t`
 *          (e.g., ULONG_MAX), as defined by @ref eya_numeric_limit_min and
 *          @ref eya_numeric_limit_max.
 *
 * @return An initialized `eya_ulong_interval_bounds` structure.
 */
#define eya_ulong_interval_bounds_initializer                                                      \
    eya_numeric_interval_bounds_initializer_by_type(eya_ulong_t)

/**
 * @def eya_ullong_interval_bounds_initializer
 * @brief Initializes an interval bounds structure for `eya_ullong_t`.
 * @details Creates an `eya_ullong_interval_bounds` structure with `lower` set to the minimum
 *          value of `eya_ullong_t` (0) and `upper` set to the maximum value of `eya_ullong_t`
 *          (e.g., ULLONG_MAX), as defined by @ref eya_numeric_limit_min and
 *          @ref eya_numeric_limit_max.
 *
 * @return An initialized `eya_ullong_interval_bounds` structure.
 */
#define eya_ullong_interval_bounds_initializer                                                     \
    eya_numeric_interval_bounds_initializer_by_type(eya_ullong_t)

/**
 * @def eya_schar_interval_bounds_initializer
 * @brief Initializes an interval bounds structure for `eya_schar_t`.
 * @details Creates an `eya_schar_interval_bounds` structure with `lower` set to the minimum
 *          value of `eya_schar_t` (e.g., SCHAR_MIN) and `upper` set to the maximum value
 *          of `eya_schar_t` (e.g., SCHAR_MAX), as defined by @ref eya_numeric_limit_min
 *          and @ref eya_numeric_limit_max.
 *
 * @return An initialized `eya_schar_interval_bounds` structure.
 */
#define eya_schar_interval_bounds_initializer                                                      \
    eya_numeric_interval_bounds_initializer_by_type(eya_schar_t)

/**
 * @def eya_sshort_interval_bounds_initializer
 * @brief Initializes an interval bounds structure for `eya_sshort_t`.
 * @details Creates an `eya_sshort_interval_bounds` structure with `lower` set to the minimum
 *          value of `eya_sshort_t` (e.g., SHRT_MIN) and `upper` set to the maximum value
 *          of `eya_sshort_t` (e.g., SHRT_MAX), as defined by @ref eya_numeric_limit_min
 *          and @ref eya_numeric_limit_max.
 *
 * @return An initialized `eya_sshort_interval_bounds` structure.
 */
#define eya_sshort_interval_bounds_initializer                                                     \
    eya_numeric_interval_bounds_initializer_by_type(eya_sshort_t)

/**
 * @def eya_sint_interval_bounds_initializer
 * @brief Initializes an interval bounds structure for `eya_sint_t`.
 * @details Creates an `eya_sint_interval_bounds` structure with `lower` set to the minimum
 *          value of `eya_sint_t` (e.g., INT_MIN) and `upper` set to the maximum value
 *          of `eya_sint_t` (e.g., INT_MAX), as defined by @ref eya_numeric_limit_min
 *          and @ref eya_numeric_limit_max.
 *
 * @return An initialized `eya_sint_interval_bounds` structure.
 */
#define eya_sint_interval_bounds_initializer                                                       \
    eya_numeric_interval_bounds_initializer_by_type(eya_sint_t)

/**
 * @def eya_slong_interval_bounds_initializer
 * @brief Initializes an interval bounds structure for `eya_slong_t`.
 * @details Creates an `eya_slong_interval_bounds` structure with `lower` set to the minimum
 *          value of `eya_slong_t` (e.g., LONG_MIN) and `upper` set to the maximum value
 *          of `eya_slong_t` (e.g., LONG_MAX), as defined by @ref eya_numeric_limit_min
 *          and @ref eya_numeric_limit_max.
 *
 * @return An initialized `eya_slong_interval_bounds` structure.
 */
#define eya_slong_interval_bounds_initializer                                                      \
    eya_numeric_interval_bounds_initializer_by_type(eya_slong_t)

/**
 * @def eya_sllong_interval_bounds_initializer
 * @brief Initializes an interval bounds structure for `eya_sllong_t`.
 * @details Creates an `eya_sllong_interval_bounds` structure with `lower` set to the minimum
 *          value of `eya_sllong_t` (e.g., LLONG_MIN) and `upper` set to the maximum value
 *          of `eya_sllong_t` (e.g., LLONG_MAX), as defined by @ref eya_numeric_limit_min
 *          and @ref eya_numeric_limit_max.
 *
 * @return An initialized `eya_sllong_interval_bounds` structure.
 */
#define eya_sllong_interval_bounds_initializer                                                     \
    eya_numeric_interval_bounds_initializer_by_type(eya_sllong_t)

#endif // EYA_NUMERIC_INTERVAL_BOUNDS_INITIALIZER_H