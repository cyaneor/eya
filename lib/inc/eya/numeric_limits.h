/**
 * @file numeric_limits.h
 * @brief Numeric type limits and size definitions.
 *
 * This header provides a unified interface to query type sizes and numeric
 * limits for fixed-width integer types (`eya_uchar_t`, `eya_uint_t`, etc.) in
 * both C and C++. Designed for compiler and architecture independence.
 */

#ifndef EYA_NUMERIC_LIMITS_H
#define EYA_NUMERIC_LIMITS_H

#include <eya/numeric_interval.h>

/**
 * @def EYA_CHAR_T_SIZE
 * @brief Size in bytes of the `eya_uchar_t` type.
 */
#ifndef EYA_CHAR_T_SIZE
#    define EYA_CHAR_T_SIZE eya_type_size(eya_uchar_t)
#endif // EYA_CHAR_T_SIZE

/**
 * @def EYA_SHORT_T_SIZE
 * @brief Size in bytes of the `eya_ushort_t` type.
 */
#ifndef EYA_SHORT_T_SIZE
#    define EYA_SHORT_T_SIZE eya_type_size(eya_ushort_t)
#endif // EYA_SHORT_T_SIZE

/**
 * @def EYA_INT_T_SIZE
 * @brief Size in bytes of the `eya_uint_t` type.
 */
#ifndef EYA_INT_T_SIZE
#    define EYA_INT_T_SIZE eya_type_size(eya_uint_t)
#endif // EYA_INT_T_SIZE

/**
 * @def EYA_LONG_T_SIZE
 * @brief Size in bytes of the `eya_ulong_t` type.
 */
#ifndef EYA_LONG_T_SIZE
#    define EYA_LONG_T_SIZE eya_type_size(eya_ulong_t)
#endif // EYA_LONG_T_SIZE

/**
 * @def EYA_LLONG_T_SIZE
 * @brief Size in bytes of the `eya_ullong_t` type.
 */
#ifndef EYA_LLONG_T_SIZE
#    define EYA_LLONG_T_SIZE eya_type_size(eya_ullong_t)
#endif // EYA_LLONG_T_SIZE

// Unsigned Types: MIN/MAX Macros

/**
 * @def EYA_UCHAR_T_MIN
 * @brief Minimum value of the `eya_uchar_t` type.
 */
#ifndef EYA_UCHAR_T_MIN
#    define EYA_UCHAR_T_MIN EYA_UCHAR_INTERVAL.bounds.lower
#endif // EYA_UCHAR_T_MIN

/**
 * @def EYA_UCHAR_T_MAX
 * @brief Maximum value of the `eya_uchar_t` type.
 */
#ifndef EYA_UCHAR_T_MAX
#    define EYA_UCHAR_T_MAX EYA_UCHAR_INTERVAL.bounds.upper
#endif // EYA_UCHAR_T_MAX

/**
 * @def EYA_USHORT_T_MIN
 * @brief Minimum value of the `eya_ushort_t` type.
 */
#ifndef EYA_USHORT_T_MIN
#    define EYA_USHORT_T_MIN EYA_USHORT_INTERVAL.bounds.lower
#endif // EYA_USHORT_T_MIN

/**
 * @def EYA_USHORT_T_MAX
 * @brief Maximum value of the `eya_ushort_t` type.
 */
#ifndef EYA_USHORT_T_MAX
#    define EYA_USHORT_T_MAX EYA_USHORT_INTERVAL.bounds.upper
#endif //  EYA_USHORT_T_MAX

/**
 * @def EYA_UINT_T_MIN
 * @brief Minimum value of the `eya_uint_t` type.
 */
#ifndef EYA_UINT_T_MIN
#    define EYA_UINT_T_MIN EYA_UINT_INTERVAL.bounds.lower
#endif // EYA_UINT_T_MIN

/**
 * @def EYA_UINT_T_MAX
 * @brief Maximum value of the `eya_uint_t` type.
 */
#ifndef EYA_UINT_T_MAX
#    define EYA_UINT_T_MAX EYA_UINT_INTERVAL.bounds.upper
#endif //  EYA_UINT_T_MAX

/**
 * @def EYA_ULONG_T_MIN
 * @brief Minimum value of the `eya_ulong_t` type.
 */
#ifndef EYA_ULONG_T_MIN
#    define EYA_ULONG_T_MIN EYA_ULONG_INTERVAL.bounds.lower
#endif // EYA_ULONG_T_MIN

/**
 * @def EYA_ULONG_T_MAX
 * @brief Maximum value of the `eya_ulong_t` type.
 */
#ifndef EYA_ULONG_T_MAX
#    define EYA_ULONG_T_MAX EYA_ULONG_INTERVAL.bounds.upper
#endif //  EYA_ULONG_T_MAX

/**
 * @def EYA_ULLONG_T_MIN
 * @brief Minimum value of the `eya_ullong_t` type.
 */
#ifndef EYA_ULLONG_T_MIN
#    define EYA_ULLONG_T_MIN EYA_ULLONG_INTERVAL.bounds.lower
#endif // EYA_ULLONG_T_MIN

/**
 * @def EYA_ULLONG_T_MAX
 * @brief Maximum value of the `eya_ullong_t` type.
 */
#ifndef EYA_ULLONG_T_MAX
#    define EYA_ULLONG_T_MAX EYA_ULLONG_INTERVAL.bounds.upper
#endif //  EYA_ULLONG_T_MAX

// Signed Types: MIN/MAX Macros

/**
 * @def EYA_SCHAR_T_MIN
 * @brief Minimum value of the `eya_schar_t` type.
 */
#ifndef EYA_SCHAR_T_MIN
#    define EYA_SCHAR_T_MIN EYA_SCHAR_INTERVAL.bounds.lower
#endif // EYA_SCHAR_T_MIN

/**
 * @def EYA_SCHAR_T_MAX
 * @brief Maximum value of the `eya_schar_t` type.
 */
#ifndef EYA_SCHAR_T_MAX
#    define EYA_SCHAR_T_MAX EYA_SCHAR_INTERVAL.bounds.upper
#endif // EYA_SCHAR_T_MAX

/**
 * @def EYA_SSHORT_T_MIN
 * @brief Minimum value of the `eya_sshort_t` type.
 */
#ifndef EYA_SSHORT_T_MIN
#    define EYA_SSHORT_T_MIN EYA_SSHORT_INTERVAL.bounds.lower
#endif // EYA_SSHORT_T_MIN

/**
 * @def EYA_SSHORT_T_MAX
 * @brief Maximum value of the `eya_sshort_t` type.
 */
#ifndef EYA_SSHORT_T_MAX
#    define EYA_SSHORT_T_MAX EYA_SSHORT_INTERVAL.bounds.upper
#endif //  EYA_SSHORT_T_MAX

/**
 * @def EYA_SINT_T_MIN
 * @brief Minimum value of the `eya_sint_t` type.
 */
#ifndef EYA_SINT_T_MIN
#    define EYA_SINT_T_MIN EYA_SINT_INTERVAL.bounds.lower
#endif // EYA_SINT_T_MIN

/**
 * @def EYA_SINT_T_MAX
 * @brief Maximum value of the `eya_sint_t` type.
 */
#ifndef EYA_SINT_MAX
#    define EYA_SINT_T_MAX EYA_SINT_INTERVAL.bounds.upper
#endif //  EYA_SINT_MAX

/**
 * @def EYA_SLONG_T_MIN
 * @brief Minimum value of the `eya_slong_t` type.
 */
#ifndef EYA_SLONG_T_MIN
#    define EYA_SLONG_T_MIN EYA_SLONG_INTERVAL.bounds.lower
#endif // EYA_SLONG_T_MIN

/**
 * @def EYA_SLONG_T_MAX
 * @brief Maximum value of the `eya_slong_t` type.
 */
#ifndef EYA_SLONG_T_MAX
#    define EYA_SLONG_T_MAX EYA_SLONG_INTERVAL.bounds.upper
#endif //  EYA_SLONG_T_MAX

/**
 * @def EYA_SLLONG_T_MIN
 * @brief Minimum value of the `eya_sllong_t` type.
 */
#ifndef EYA_SLLONG_T_MIN
#    define EYA_SLLONG_T_MIN EYA_SLLONG_INTERVAL.bounds.lower
#endif // EYA_SLLONG_T_MIN

/**
 * @def EYA_SLLONG_T_MAX
 * @brief Maximum value of the `eya_sllong_t` type.
 */
#ifndef EYA_SLLONG_T_MAX
#    define EYA_SLLONG_T_MAX EYA_SLLONG_INTERVAL.bounds.upper
#endif //  EYA_SLLONG_T_MAX

#endif // EYA_NUMERIC_LIMITS_H