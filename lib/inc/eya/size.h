/**
 * @file size.h
 * @brief Platform-specific size type definitions
 *
 * This header defines platform-specific signed and unsigned size types
 * (eya_ssize_t and eya_usize_t) along with their minimum and maximum values.
 *
 * The actual types depend on the platform (Windows vs others)
 * and bit depth (32-bit vs 64-bit on Windows).
 */

#ifndef EYA_SIZE_H
#define EYA_SIZE_H

#include "numeric_fixed.h"

#if EYA_COMPILER_OS_TYPE == EYA_COMPILER_OS_TYPE_WINDOWS
#    if EYA_COMPILER_BIT_DEPTH == 64
/**
 * @def EYA_SIZE_SIZE
 * @brief Size type identifier for 64-bit Windows platforms
 * @details Defined as EYA_LLONG_SIZE indicating long long type size is used
 */
#        define EYA_SIZE_SIZE EYA_LLONG_SIZE

/**
 * @def EYA_SSIZE_MIN
 * @brief Minimum value for signed size type (Windows, 64-bit)
 * @details Defined as EYA_SLLONG_MIN for 64-bit Windows platforms
 */
#        define EYA_SSIZE_MIN EYA_SLLONG_MIN

/**
 * @def EYA_SSIZE_MAX
 * @brief Maximum value for signed size type (Windows, 64-bit)
 * @details Defined as EYA_SLLONG_MAX for 64-bit Windows platforms
 */
#        define EYA_SSIZE_MAX EYA_SLLONG_MAX

/**
 * @typedef eya_ssize_t
 * @brief Signed integer type for representing sizes or counts (Windows, 64-bit)
 * @details Alias for eya_s64_t on 64-bit Windows platforms
 */
typedef eya_s64_t eya_ssize_t;

/**
 * @def EYA_USIZE_MIN
 * @brief Minimum value (0) for unsigned size type (Windows, 64-bit)
 * @details Defined as EYA_ULLONG_MIN (0) for 64-bit Windows platforms
 */
#        define EYA_USIZE_MIN EYA_ULLONG_MIN

/**
 * @def EYA_USIZE_MAX
 * @brief Maximum value for unsigned size type (Windows, 64-bit)
 * @details Defined as EYA_ULLONG_MAX for 64-bit Windows platforms
 */
#        define EYA_USIZE_MAX EYA_ULLONG_MAX

/**
 * @typedef eya_usize_t
 * @brief Unsigned integer type for representing sizes or counts (Windows, 64-bit)
 * @details Alias for eya_u64_t on 64-bit Windows platforms
 */
typedef eya_u64_t eya_usize_t;
#    else /* EYA_COMPILER_OS_TYPE != EYA_COMPILER_OS_TYPE_WINDOWS */
/**
 * @def EYA_SIZE_SIZE
 * @brief Size type identifier for 32-bit Windows platforms
 * @details Defined as EYA_INT_SIZE indicating int type size is used
 */
#        define EYA_SIZE_SIZE EYA_INT_SIZE

/**
 * @def EYA_SSIZE_MIN
 * @brief Minimum value for signed size type (Windows, 32-bit)
 * @details Defined as EYA_SINT_MIN for 32-bit Windows platforms
 */
#        define EYA_SSIZE_MIN EYA_SINT_MIN

/**
 * @def EYA_SSIZE_MAX
 * @brief Maximum value for signed size type (Windows, 32-bit)
 * @details Defined as EYA_SINT_MAX for 32-bit Windows platforms
 */
#        define EYA_SSIZE_MAX EYA_SINT_MAX

/**
 * @typedef eya_ssize_t
 * @brief Signed integer type for representing sizes or counts (Windows, 32-bit)
 * @details Alias for eya_sint_t on 32-bit Windows platforms
 */
typedef eya_sint_t eya_ssize_t;

/**
 * @def EYA_USIZE_MIN
 * @brief Minimum value (0) for unsigned size type (Windows, 32-bit)
 * @details Defined as EYA_UINT_MIN (0) for 32-bit Windows platforms
 */
#        define EYA_USIZE_MIN EYA_UINT_MIN

/**
 * @def EYA_USIZE_MAX
 * @brief Maximum value for unsigned size type (Windows, 32-bit)
 * @details Defined as EYA_UINT_MAX for 32-bit Windows platforms
 */
#        define EYA_USIZE_MAX EYA_UINT_MAX

/**
 * @typedef eya_usize_t
 * @brief Unsigned integer type for representing sizes or counts (Windows, 32-bit)
 * @details Alias for eya_uint_t on 32-bit Windows platforms
 */
typedef eya_uint_t eya_usize_t;
#    endif
#else /* EYA_COMPILER_OS_TYPE == EYA_COMPILER_OS_TYPE_WINDOWS */
/**
 * @def EYA_SIZE_SIZE
 * @brief Size type identifier for non-Windows platforms
 * @details Defined as EYA_LONG_SIZE indicating long type size is used
 */
#    define EYA_SIZE_SIZE EYA_LONG_SIZE

/**
 * @def EYA_SSIZE_MIN
 * @brief Minimum value for platform's native signed size type
 * @details Defined as EYA_SLONG_MIN for non-Windows platforms
 */
#    define EYA_SSIZE_MIN EYA_SLONG_MIN

/**
 * @def EYA_SSIZE_MAX
 * @brief Maximum value for platform's native signed size type
 * @details Defined as EYA_SLONG_MAX for non-Windows platforms
 */
#    define EYA_SSIZE_MAX EYA_SLONG_MAX

/**
 * @typedef eya_ssize_t
 * @brief Platform's native signed type for representing sizes or counts
 * @details Alias for eya_slong_t on non-Windows platforms
 */
typedef eya_slong_t eya_ssize_t;

/**
 * @def EYA_USIZE_MIN
 * @brief Minimum value (0) for platform's native unsigned size type
 * @details Defined as EYA_ULONG_MIN (0) for non-Windows platforms
 */
#    define EYA_USIZE_MIN EYA_ULONG_MIN

/**
 * @def EYA_USIZE_MAX
 * @brief Maximum value for platform's native unsigned size type
 * @details Defined as EYA_ULONG_MAX for non-Windows platforms
 */
#    define EYA_USIZE_MAX EYA_ULONG_MAX

/**
 * @typedef eya_usize_t
 * @brief Platform's native unsigned type for representing sizes or counts
 * @details Alias for eya_ulong_t on non-Windows platforms
 */
typedef eya_ulong_t eya_usize_t;
#endif

#endif // EYA_SIZE_H