/**
 * @file numeric_fixed_limits.h
 * @brief Limits and size definitions for fixed-width integer types
 *
 * Defines size constants and value limits for fixed-size integer types declared
 * in `numeric_fixed_types.h`. These macros provide architecture-independent
 * specifications of type properties for cross-platform compatibility.
 *
 * @details Contains macro definitions for:
 *          - Type sizes in bytes (EYA_*_SIZE)
 *          - Minimum values (EYA_*_MIN)
 *          - Maximum values (EYA_*_MAX)
 *
 * All values are derived from base numeric types defined in `numeric_limits.h`
 * to maintain consistency with underlying type implementations.
 *
 * @note Use these macros instead of hardcoding values
 *       to ensure portability across different platforms and compilers.
 */

#ifndef EYA_NUMERIC_FIXED_LIMITS_H
#define EYA_NUMERIC_FIXED_LIMITS_H

#include "numeric_limits.h"

/**
 * @def EYA_U8_SIZE
 * @brief Size in bytes of `eya_u8_t` type
 * @details Equals to `EYA_CHAR_SIZE` from base numeric limits
 */
#define EYA_U8_SIZE EYA_CHAR_SIZE

/**
 * @def EYA_U8_MIN
 * @brief Minimum value of `eya_u8_t` type
 * @details Alias for `EYA_UCHAR_MIN` (typically 0)
 */
#define EYA_U8_MIN EYA_UCHAR_MIN

/**
 * @def EYA_U8_MAX
 * @brief Maximum value of `eya_u8_t` type
 * @details Alias for `EYA_UCHAR_MAX` (typically 255)
 */
#define EYA_U8_MAX EYA_UCHAR_MAX

/**
 * @def EYA_U16_SIZE
 * @brief Size in bytes of `eya_u16_t` type
 * @details Equals to `EYA_SHORT_SIZE` from base numeric limits
 */
#define EYA_U16_SIZE EYA_SHORT_SIZE

/**
 * @def EYA_U16_MIN
 * @brief Minimum value of `eya_u16_t` type
 * @details Alias for `EYA_USHORT_MIN` (typically 0)
 */
#define EYA_U16_MIN EYA_USHORT_MIN

/**
 * @def EYA_U16_MAX
 * @brief Maximum value of `eya_u16_t` type
 * @details Alias for `EYA_USHORT_MAX` (typically 65,535)
 */
#define EYA_U16_MAX EYA_USHORT_MAX

/**
 * @def EYA_U32_SIZE
 * @brief Size in bytes of `eya_u32_t` type
 * @details Equals to `EYA_INT_SIZE` from base numeric limits
 */
#define EYA_U32_SIZE EYA_INT_SIZE

/**
 * @def EYA_U32_MIN
 * @brief Minimum value of `eya_u32_t` type
 * @details Alias for `EYA_UINT_MIN` (typically 0)
 */
#define EYA_U32_MIN EYA_UINT_MIN

/**
 * @def EYA_U32_MAX
 * @brief Maximum value of `eya_u32_t` type
 * @details Alias for `EYA_UINT_MAX` (typically 4,294,967,295)
 */
#define EYA_U32_MAX EYA_UINT_MAX

/**
 * @def EYA_U64_SIZE
 * @brief Size in bytes of `eya_u64_t` type
 * @details Equals to `EYA_LLONG_SIZE` from base numeric limits
 */
#define EYA_U64_SIZE EYA_LLONG_SIZE

/**
 * @def EYA_U64_MIN
 * @brief Minimum value of `eya_u64_t` type
 * @details Alias for `EYA_ULLONG_MIN` (typically 0)
 */
#define EYA_U64_MIN EYA_ULLONG_MIN

/**
 * @def EYA_U64_MAX
 * @brief Maximum value of `eya_u64_t` type
 * @details Alias for `EYA_ULLONG_MAX` (typically 18,446,744,073,709,551,615)
 */
#define EYA_U64_MAX EYA_ULLONG_MAX

/**
 * @def EYA_S8_SIZE
 * @brief Size in bytes of `eya_s8_t` type
 * @details Equals to `EYA_CHAR_SIZE` from base numeric limits
 */
#define EYA_S8_SIZE EYA_CHAR_SIZE

/**
 * @def EYA_S8_MIN
 * @brief Minimum value of `eya_s8_t` type
 * @details Alias for `EYA_SCHAR_MIN` (typically -128)
 */
#define EYA_S8_MIN EYA_SCHAR_MIN

/**
 * @def EYA_S8_MAX
 * @brief Maximum value of `eya_s8_t` type
 * @details Alias for `EYA_SCHAR_MAX` (typically 127)
 */
#define EYA_S8_MAX EYA_SCHAR_MAX

/**
 * @def EYA_S16_SIZE
 * @brief Size in bytes of `eya_s16_t` type
 * @details Equals to `EYA_SHORT_SIZE` from base numeric limits
 */
#define EYA_S16_SIZE EYA_SHORT_SIZE

/**
 * @def EYA_S16_MIN
 * @brief Minimum value of `eya_s16_t` type
 * @details Alias for `EYA_SSHORT_MIN` (typically -32,768)
 */
#define EYA_S16_MIN EYA_SSHORT_MIN

/**
 * @def EYA_S16_MAX
 * @brief Maximum value of `eya_s16_t` type
 * @details Alias for `EYA_SSHORT_MAX` (typically 32,767)
 */
#define EYA_S16_MAX EYA_SSHORT_MAX

/**
 * @def EYA_S32_SIZE
 * @brief Size in bytes of `eya_s32_t` type
 * @details Equals to `EYA_INT_SIZE` from base numeric limits
 */
#define EYA_S32_SIZE EYA_INT_SIZE

/**
 * @def EYA_S32_MIN
 * @brief Minimum value of `eya_s32_t` type
 * @details Alias for `EYA_SINT_MIN` (typically -2,147,483,648)
 */
#define EYA_S32_MIN EYA_SINT_MIN

/**
 * @def EYA_S32_MAX
 * @brief Maximum value of `eya_s32_t` type
 * @details Alias for `EYA_SINT_MAX` (typically 2,147,483,647)
 */
#define EYA_S32_MAX EYA_SINT_MAX

/**
 * @def EYA_S64_SIZE
 * @brief Size in bytes of `eya_s64_t` type
 * @details Equals to `EYA_LLONG_SIZE` from base numeric limits
 */
#define EYA_S64_SIZE EYA_LLONG_SIZE

/**
 * @def EYA_S64_MIN
 * @brief Minimum value of `eya_s64_t` type
 * @details Alias for `EYA_SLLONG_MIN` (typically -9,223,372,036,854,775,808)
 */
#define EYA_S64_MIN EYA_SLLONG_MIN

/**
 * @def EYA_S64_MAX
 * @brief Maximum value of `eya_s64_t` type
 * @details Alias for `EYA_SLLONG_MAX` (typically 9,223,372,036,854,775,807)
 */
#define EYA_S64_MAX EYA_SLLONG_MAX

#ifdef EYA_INT128_SIZE
/**
 * @def EYA_U128_SIZE
 * @brief Size in bytes of `eya_u128_t` type (if supported)
 * @details Equals to `EYA_INT128_SIZE` from base numeric limits
   @note Only defined when 128-bit types are available
 */
#    define EYA_U128_SIZE EYA_INT128_SIZE

/** @def EYA_U128_MIN
 *  @brief Minimum value of `eya_u128_t` type (if supported)
 *  @details Alias for `EYA_UINT128_MIN` (typically 0)
 */
#    define EYA_U128_MIN EYA_UINT128_MIN

/**
 * @def EYA_U128_MAX
 * @brief Maximum value of eya_u128_t type (if supported)
 * @details Alias for EYA_UINT128_MAX
 *          (typically 340,282,366,920,938,463,463,374,607,431,768,211,455)
 */
#    define EYA_U128_MAX EYA_UINT128_MAX

/**
 * @def EYA_S128_SIZE
 * @brief Size in bytes of eya_s128_t type (if supported)
 * @details Equals to EYA_INT128_SIZE from base numeric limits
 */
#    define EYA_S128_SIZE EYA_INT128_SIZE

/**
 * @def EYA_S128_MIN
 * @brief Minimum value of eya_s128_t type (if supported)
 * @details Alias for EYA_SINT128_MIN
 *          (typically -170,141,183,460,469,231,731,687,303,715,884,105,728)
 */
#    define EYA_S128_MIN EYA_SINT128_MIN

/**
 * @def EYA_S128_MAX
 * @brief Maximum value of eya_s128_t type (if supported)
 * @details Alias for EYA_SINT128_MAX
 *          (typically 170,141,183,460,469,231,731,687,303,715,884,105,727)
 */
#    define EYA_S128_MAX EYA_SINT128_MAX
#endif // EYA_INT128_SIZE

#endif // EYA_NUMERIC_FIXED_LIMITS_H