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

#include "numeric_limit.h"
#include "numeric_types.h"

/**
 * @def EYA_CHAR_SIZE
 * @brief Size in bytes of the `eya_uchar_t` type.
 */
#ifndef EYA_CHAR_SIZE
#    define EYA_CHAR_SIZE eya_type_size(eya_uchar_t)
#endif // EYA_CHAR_SIZE

/**
 * @def EYA_SHORT_SIZE
 * @brief Size in bytes of the `eya_ushort_t` type.
 */
#ifndef EYA_SHORT_SIZE
#    define EYA_SHORT_SIZE eya_type_size(eya_ushort_t)
#endif // EYA_SHORT_SIZE

/**
 * @def EYA_INT_SIZE
 * @brief Size in bytes of the `eya_uint_t` type.
 */
#ifndef EYA_INT_SIZE
#    define EYA_INT_SIZE eya_type_size(eya_uint_t)
#endif // EYA_INT_SIZE

/**
 * @def EYA_LONG_SIZE
 * @brief Size in bytes of the `eya_ulong_t` type.
 */
#ifndef EYA_LONG_SIZE
#    define EYA_LONG_SIZE eya_type_size(eya_ulong_t)
#endif // EYA_LONG_SIZE

/**
 * @def EYA_LLONG_SIZE
 * @brief Size in bytes of the `eya_ullong_t` type.
 */
#ifndef EYA_LLONG_SIZE
#    define EYA_LLONG_SIZE eya_type_size(eya_ullong_t)
#endif // EYA_LLONG_SIZE

// Unsigned Types: MIN/MAX Macros

/**
 * @def EYA_UCHAR_MIN
 * @brief Minimum value of the `eya_uchar_t` type.
 */
#ifndef EYA_UCHAR_MIN
#    define EYA_UCHAR_MIN eya_numeric_limit_min(eya_uchar_t)
#endif // EYA_UCHAR_MIN

/**
 * @def EYA_UCHAR_MAX
 * @brief Maximum value of the `eya_uchar_t` type.
 */
#ifndef EYA_UCHAR_MAX
#    define EYA_UCHAR_MAX eya_numeric_limit_max(eya_uchar_t)
#endif // EYA_UCHAR_MAX

/**
 * @def EYA_USHORT_MIN
 * @brief Minimum value of the `eya_ushort_t` type.
 */
#ifndef EYA_USHORT_MIN
#    define EYA_USHORT_MIN eya_numeric_limit_min(eya_ushort_t)
#endif // EYA_USHORT_MIN

/**
 * @def EYA_USHORT_MAX
 * @brief Maximum value of the `eya_ushort_t` type.
 */
#ifndef EYA_USHORT_MAX
#    define EYA_USHORT_MAX eya_numeric_limit_max(eya_ushort_t)
#endif // EYA_USHORT_MAX

/**
 * @def EYA_UINT_MIN
 * @brief Minimum value of the `eya_uint_t` type.
 */
#ifndef EYA_UINT_MIN
#    define EYA_UINT_MIN eya_numeric_limit_min(eya_uint_t)
#endif // EYA_UINT_MIN

/**
 * @def EYA_UINT_MAX
 * @brief Maximum value of the `eya_uint_t` type.
 */
#ifndef EYA_UINT_MAX
#    define EYA_UINT_MAX eya_numeric_limit_max(eya_uint_t)
#endif // EYA_UINT_MAX

/**
 * @def EYA_ULONG_MIN
 * @brief Minimum value of the `eya_ulong_t` type.
 */
#ifndef EYA_ULONG_MIN
#    define EYA_ULONG_MIN eya_numeric_limit_min(eya_ulong_t)
#endif // EYA_ULONG_MIN

/**
 * @def EYA_ULONG_MAX
 * @brief Maximum value of the `eya_ulong_t` type.
 */
#ifndef EYA_ULONG_MAX
#    define EYA_ULONG_MAX eya_numeric_limit_max(eya_ulong_t)
#endif // EYA_ULONG_MAX

/**
 * @def EYA_ULLONG_MIN
 * @brief Minimum value of the `eya_ullong_t` type.
 */
#ifndef EYA_ULLONG_MIN
#    define EYA_ULLONG_MIN eya_numeric_limit_min(eya_ullong_t)
#endif // EYA_ULLONG_MIN

/**
 * @def EYA_ULLONG_MAX
 * @brief Maximum value of the `eya_ullong_t` type.
 */
#ifndef EYA_ULLONG_MAX
#    define EYA_ULLONG_MAX eya_numeric_limit_max(eya_ullong_t)
#endif // EYA_ULLONG_MAX

// Signed Types: MIN/MAX Macros

/**
 * @def EYA_SCHAR_MIN
 * @brief Minimum value of the `eya_schar_t` type.
 */
#ifndef EYA_SCHAR_MIN
#    define EYA_SCHAR_MIN eya_numeric_limit_min(eya_schar_t)
#endif // EYA_SCHAR_MIN

/**
 * @def EYA_SCHAR_MAX
 * @brief Maximum value of the `eya_schar_t` type.
 */
#ifndef EYA_SCHAR_MAX
#    define EYA_SCHAR_MAX eya_numeric_limit_max(eya_schar_t)
#endif // EYA_SCHAR_MAX

/**
 * @def EYA_SSHORT_MIN
 * @brief Minimum value of the `eya_sshort_t` type.
 */
#ifndef EYA_SSHORT_MIN
#    define EYA_SSHORT_MIN eya_numeric_limit_min(eya_sshort_t)
#endif // EYA_SSHORT_MIN

/**
 * @def EYA_SSHORT_MAX
 * @brief Maximum value of the `eya_sshort_t` type.
 */
#ifndef EYA_SSHORT_MAX
#    define EYA_SSHORT_MAX eya_numeric_limit_max(eya_sshort_t)
#endif // EYA_SSHORT_MAX

/**
 * @def EYA_SINT_MIN
 * @brief Minimum value of the `eya_sint_t` type.
 */
#ifndef EYA_SINT_MIN
#    define EYA_SINT_MIN eya_numeric_limit_min(eya_sint_t)
#endif // EYA_SINT_MIN

/**
 * @def EYA_SINT_MAX
 * @brief Maximum value of the `eya_sint_t` type.
 */
#ifndef EYA_SINT_MAX
#    define EYA_SINT_MAX eya_numeric_limit_max(eya_sint_t)
#endif // EYA_SINT_MAX

/**
 * @def EYA_SLONG_MIN
 * @brief Minimum value of the `eya_slong_t` type.
 */
#ifndef EYA_SLONG_MIN
#    define EYA_SLONG_MIN eya_numeric_limit_min(eya_slong_t)
#endif // EYA_SLONG_MIN

/**
 * @def EYA_SLONG_MAX
 * @brief Maximum value of the `eya_slong_t` type.
 */
#ifndef EYA_SLONG_MAX
#    define EYA_SLONG_MAX eya_numeric_limit_max(eya_slong_t)
#endif // EYA_SLONG_MAX

/**
 * @def EYA_SLLONG_MIN
 * @brief Minimum value of the `eya_sllong_t` type.
 */
#ifndef EYA_SLLONG_MIN
#    define EYA_SLLONG_MIN eya_numeric_limit_min(eya_sllong_t)
#endif // EYA_SLLONG_MIN

/**
 * @def EYA_SLLONG_MAX
 * @brief Maximum value of the `eya_sllong_t` type.
 */
#ifndef EYA_SLLONG_MAX
#    define EYA_SLLONG_MAX eya_numeric_limit_max(eya_sllong_t)
#endif // EYA_SLLONG_MAX

#ifdef EYA_INT128_SIZE
/**
 * @def EYA_UINT128_MIN
 * @brief Maximum value of the `eya_uint128_t` type.
 */
#    ifndef EYA_UINT128_MIN
#        define EYA_UINT128_MIN eya_numeric_limit_min(eya_uint128_t)
#    endif // EYA_UINT128_MIN

/**
 * @def EYA_UINT128_MAX
 * @brief Maximum value of the `eya_uint128_t` type.
 */
#    ifndef EYA_UINT128_MAX
#        define EYA_UINT128_MAX eya_numeric_limit_max(eya_uint128_t)
#    endif // EYA_UINT128_MAX

/**
 * @def EYA_SINT128_MIN
 * @brief Maximum value of the `eya_sint128_t` type.
 */
#    ifndef EYA_SINT128_MIN
#        define EYA_SINT128_MIN eya_numeric_limit_min(eya_sint128_t)
#    endif // EYA_SINT128_MIN

/**
 * @def EYA_SINT128_MAX
 * @brief Maximum value of the `eya_sint128_t` type.
 */
#    ifndef EYA_SINT128_MAX
#        define EYA_SINT128_MAX eya_numeric_limit_max(eya_sint128_t)
#    endif // EYA_SINT128_MAX
#endif     // EYA_INT128_SIZE

#endif // EYA_NUMERIC_LIMITS_H