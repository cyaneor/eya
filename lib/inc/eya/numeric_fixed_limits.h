/**
 * @file numeric_fixed_limits.h
 * @brief Limits and size definitions for fixed-width integer types
 *
 * Defines size constants and value limits for fixed-size integer types declared
 * in `numeric_fixed_types.h`. These macros provide architecture-independent
 * specifications of type properties for cross-platform compatibility.
 *
 * @details Contains macro definitions for:
 *          - Type sizes in bytes (EYA_*_T_SIZE)
 *          - Minimum values (EYA_*_T_MIN)
 *          - Maximum values (EYA_*_T_MAX)
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
 * @def EYA_U8_T_SIZE
 * @brief Size in bytes of `eya_u8_t` type
 * @details Equals to `EYA_CHAR_T_SIZE` from base numeric limits
 */
#define EYA_U8_T_SIZE EYA_CHAR_T_SIZE

/**
 * @def EYA_U8_T_MIN
 * @brief Minimum value of `eya_u8_t` type
 * @details Alias for `EYA_UCHAR_T_MIN` (typically 0)
 */
#define EYA_U8_T_MIN EYA_UCHAR_T_MIN

/**
 * @def EYA_U8_T_MAX
 * @brief Maximum value of `eya_u8_t` type
 * @details Alias for `EYA_UCHAR_T_MAX` (typically 255)
 */
#define EYA_U8_T_MAX EYA_UCHAR_T_MAX

/**
 * @def EYA_U16_T_SIZE
 * @brief Size in bytes of `eya_u16_t` type
 * @details Equals to `EYA_SHORT_T_SIZE` from base numeric limits
 */
#define EYA_U16_T_SIZE EYA_SHORT_T_SIZE

/**
 * @def EYA_U16_T_MIN
 * @brief Minimum value of `eya_u16_t` type
 * @details Alias for `EYA_USHORT_T_MIN` (typically 0)
 */
#define EYA_U16_T_MIN EYA_USHORT_T_MIN

/**
 * @def EYA_U16_T_MAX
 * @brief Maximum value of `eya_u16_t` type
 * @details Alias for `EYA_USHORT_T_MAX` (typically 65,535)
 */
#define EYA_U16_T_MAX EYA_USHORT_T_MAX

/**
 * @def EYA_U32_T_SIZE
 * @brief Size in bytes of `eya_u32_t` type
 * @details Equals to `EYA_INT_T_SIZE` from base numeric limits
 */
#define EYA_U32_T_SIZE EYA_INT_T_SIZE

/**
 * @def EYA_U32_T_MIN
 * @brief Minimum value of `eya_u32_t` type
 * @details Alias for `EYA_UINT_T_MIN` (typically 0)
 */
#define EYA_U32_T_MIN EYA_UINT_T_MIN

/**
 * @def EYA_U32_T_MAX
 * @brief Maximum value of `eya_u32_t` type
 * @details Alias for `EYA_UINT_T_MAX` (typically 4,294,967,295)
 */
#define EYA_U32_T_MAX EYA_UINT_T_MAX

/**
 * @def EYA_U64_T_SIZE
 * @brief Size in bytes of `eya_u64_t` type
 * @details Equals to `EYA_LLONG_T_SIZE` from base numeric limits
 */
#define EYA_U64_T_SIZE EYA_LLONG_T_SIZE

/**
 * @def EYA_U64_T_MIN
 * @brief Minimum value of `eya_u64_t` type
 * @details Alias for `EYA_ULLONG_T_MIN` (typically 0)
 */
#define EYA_U64_T_MIN EYA_ULLONG_T_MIN

/**
 * @def EYA_U64_T_MAX
 * @brief Maximum value of `eya_u64_t` type
 * @details Alias for `EYA_ULLONG_T_MAX` (typically 18,446,744,073,709,551,615)
 */
#define EYA_U64_T_MAX EYA_ULLONG_T_MAX

/**
 * @def EYA_S8_T_SIZE
 * @brief Size in bytes of `eya_s8_t` type
 * @details Equals to `EYA_CHAR_T_SIZE` from base numeric limits
 */
#define EYA_S8_T_SIZE EYA_CHAR_T_SIZE

/**
 * @def EYA_S8_T_MIN
 * @brief Minimum value of `eya_s8_t` type
 * @details Alias for `EYA_SCHAR_T_MIN` (typically -128)
 */
#define EYA_S8_T_MIN EYA_SCHAR_T_MIN

/**
 * @def EYA_S8_T_MAX
 * @brief Maximum value of `eya_s8_t` type
 * @details Alias for `EYA_SCHAR_T_MAX` (typically 127)
 */
#define EYA_S8_T_MAX EYA_SCHAR_T_MAX

/**
 * @def EYA_S16_T_SIZE
 * @brief Size in bytes of `eya_s16_t` type
 * @details Equals to `EYA_SHORT_T_SIZE` from base numeric limits
 */
#define EYA_S16_T_SIZE EYA_SHORT_T_SIZE

/**
 * @def EYA_S16_T_MIN
 * @brief Minimum value of `eya_s16_t` type
 * @details Alias for `EYA_SSHORT_T_MIN` (typically -32,768)
 */
#define EYA_S16_T_MIN EYA_SSHORT_T_MIN

/**
 * @def EYA_S16_T_MAX
 * @brief Maximum value of `eya_s16_t` type
 * @details Alias for `EYA_SSHORT_T_MAX` (typically 32,767)
 */
#define EYA_S16_T_MAX EYA_SSHORT_T_MAX

/**
 * @def EYA_S32_T_SIZE
 * @brief Size in bytes of `eya_s32_t` type
 * @details Equals to `EYA_INT_T_SIZE` from base numeric limits
 */
#define EYA_S32_T_SIZE EYA_INT_T_SIZE

/**
 * @def EYA_S32_T_MIN
 * @brief Minimum value of `eya_s32_t` type
 * @details Alias for `EYA_SINT_T_MIN` (typically -2,147,483,648)
 */
#define EYA_S32_T_MIN EYA_SINT_T_MIN

/**
 * @def EYA_S32_T_MAX
 * @brief Maximum value of `eya_s32_t` type
 * @details Alias for `EYA_SINT_T_MAX` (typically 2,147,483,647)
 */
#define EYA_S32_T_MAX EYA_SINT_T_MAX

/**
 * @def EYA_S64_T_SIZE
 * @brief Size in bytes of `eya_s64_t` type
 * @details Equals to `EYA_LLONG_T_SIZE` from base numeric limits
 */
#define EYA_S64_T_SIZE EYA_LLONG_T_SIZE

/**
 * @def EYA_S64_T_MIN
 * @brief Minimum value of `eya_s64_t` type
 * @details Alias for `EYA_SLLONG_T_MIN` (typically -9,223,372,036,854,775,808)
 */
#define EYA_S64_T_MIN EYA_SLLONG_T_MIN

/**
 * @def EYA_S64_T_MAX
 * @brief Maximum value of `eya_s64_t` type
 * @details Alias for `EYA_SLLONG_T_MAX` (typically 9,223,372,036,854,775,807)
 */
#define EYA_S64_T_MAX EYA_SLLONG_T_MAX

#endif // EYA_NUMERIC_FIXED_LIMITS_H