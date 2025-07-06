/**
 * @file size.h
 * @brief Header file defining signed
 *        and unsigned size types (`eya_ssize_t` and `eya_usize_t`).
 *
 * This header defines platform-appropriate size types (signed and unsigned)
 * with their corresponding minimum and maximum values.
 *
 * The implementation varies depending on the platform (Windows vs others)
 * and can be customized by defining EYA_SIZE_T_SIZE.
 */

#ifndef EYA_SIZE_H
#define EYA_SIZE_H

#include "numeric_fixed.h"

#ifndef EYA_SIZE_T_SIZE
#    if EYA_COMPILER_OS_TYPE == EYA_COMPILER_OS_TYPE_WINDOWS
#        define EYA_SIZE_T_SIZE EYA_LLONG_T_SIZE

/**
 * @def EYA_SSIZE_T_MIN
 * @brief Minimum value for Windows signed size type
 */
#        define EYA_SSIZE_T_MIN EYA_SLLONG_T_MIN

/**
 * @def EYA_SSIZE_T_MAX
 * @brief Maximum value for Windows signed size type
 */
#        define EYA_SSIZE_T_MAX EYA_SLLONG_T_MAX

/**
 * @typedef eya_ssize_t
 * @brief Signed integer type for representing sizes or counts (Windows)
 */
typedef eya_s64_t eya_ssize_t;

/**
 * @def EYA_USIZE_T_MIN
 * @brief Minimum value for Windows unsigned size type
 */
#        define EYA_USIZE_T_MIN EYA_ULLONG_T_MIN

/**
 * @def EYA_USIZE_T_MAX
 * @brief Maximum value for Windows unsigned size type
 */
#        define EYA_USIZE_T_MAX EYA_ULLONG_T_MAX

/**
 * @typedef eya_usize_t
 * @brief Unsigned integer type for representing sizes or counts (Windows)
 */
typedef eya_u64_t eya_usize_t;
#    else
#        define EYA_SIZE_T_SIZE EYA_LONG_T_SIZE

/**
 * @def EYA_SSIZE_T_MIN
 * @brief Minimum value for platform's native signed long size type
 */
#        define EYA_SSIZE_T_MIN EYA_SLONG_T_MIN

/**
 * @def EYA_SSIZE_T_MAX
 * @brief Maximum value for platform's native signed long size type
 */
#        define EYA_SSIZE_T_MAX EYA_SLONG_T_MAX

/**
 * @typedef eya_ssize_t
 * @brief Platform's native signed long type for representing sizes or counts
 */
typedef eya_slong_t eya_ssize_t;

/**
 * @def EYA_USIZE_T_MIN
 * @brief Minimum value for platform's native unsigned long size type
 */
#        define EYA_USIZE_T_MIN EYA_ULONG_T_MIN

/**
 * @def EYA_USIZE_T_MAX
 * @brief Maximum value for platform's native unsigned long size type
 */
#        define EYA_USIZE_T_MAX EYA_ULONG_T_MAX

/**
 * @typedef eya_usize_t
 * @brief Platform's native unsigned long type for representing sizes or counts
 */
typedef eya_ulong_t eya_usize_t;
#    endif
#else
#    if EYA_SIZE_T_SIZE == 8
#        ifndef EYA_SSIZE_T_MIN
/**
 * @def EYA_SSIZE_T_MIN
 * @brief Minimum value for signed size type (64-bit)
 */
#            define EYA_SSIZE_T_MIN EYA_S64_T_MIN
#        endif

#        ifndef EYA_SSIZE_T_MAX
/**
 * @def EYA_SSIZE_T_MAX
 * @brief Maximum value for signed size type (64-bit)
 */
#            define EYA_SSIZE_T_MAX EYA_S64_T_MAX
#        endif

/**
 * @typedef eya_ssize_t
 * @brief Signed 64-bit integer type for representing sizes or counts
 */
typedef eya_s64_t eya_ssize_t;

#        ifndef EYA_USIZE_T_MIN
/**
 * @def EYA_USIZE_T_MIN
 * @brief Minimum value for unsigned size type (64-bit)
 */
#            define EYA_USIZE_T_MIN EYA_U64_T_MIN
#        endif

#        ifndef EYA_USIZE_T_MAX
/**
 * @def EYA_USIZE_T_MAX
 * @brief Maximum value for unsigned size type (64-bit)
 */
#            define EYA_USIZE_T_MAX EYA_U64_T_MAX
#        endif

/**
 * @typedef eya_usize_t
 * @brief Unsigned 64-bit integer type for representing sizes or counts
 */
typedef eya_u64_t eya_usize_t;

#    elif EYA_SIZE_T_SIZE == 4
#        ifndef EYA_SSIZE_T_MIN
/**
 * @def EYA_SSIZE_T_MIN
 * @brief Minimum value for signed size type (32-bit)
 */
#            define EYA_SSIZE_T_MIN EYA_S32_T_MIN
#        endif

#        ifndef EYA_SSIZE_T_MAX
/**
 * @def EYA_SSIZE_T_MAX
 * @brief Maximum value for signed size type (32-bit)
 */
#            define EYA_SSIZE_T_MAX EYA_S32_T_MAX
#        endif

/**
 * @typedef eya_ssize_t
 * @brief Signed 32-bit integer type for representing sizes or counts
 *  Alias for s32_t
 */
typedef eya_s32_t eya_ssize_t;

#        ifndef EYA_USIZE_T_MIN
/**
 * @def EYA_USIZE_T_MIN
 * @brief Minimum value for unsigned size type (32-bit)
 */
#            define EYA_USIZE_T_MIN EYA_U32_T_MIN
#        endif

#        ifndef EYA_USIZE_T_MAX
/**
 * @def EYA_USIZE_T_MAX
 * @brief Maximum value for unsigned size type (32-bit)
 */
#            define EYA_USIZE_T_MAX EYA_U32_T_MAX
#        endif

/**
 * @typedef eya_usize_t
 * @brief Unsigned 32-bit integer type for representing sizes or counts
 *  Alias for u32_t
 */
typedef eya_u32_t eya_usize_t;

#    elif EYA_SIZE_T_SIZE == 2
#        ifndef EYA_SSIZE_T_MIN
/**
 * @def EYA_SSIZE_T_MIN
 * @brief Minimum value for signed size type (16-bit)
 */
#            define EYA_SSIZE_T_MIN EYA_S16_T_MIN
#        endif

#        ifndef EYA_SSIZE_T_MAX
/**
 * @def EYA_SSIZE_T_MAX
 * @brief Maximum value for signed size type (16-bit)
 */
#            define EYA_SSIZE_T_MAX EYA_S16_T_MAX
#        endif

/**
 * @typedef eya_ssize_t
 * @brief Signed 16-bit integer type for representing sizes or counts
 */
typedef eya_s16_t eya_ssize_t;

#        ifndef EYA_USIZE_T_MIN
/**
 * @def EYA_USIZE_T_MIN
 * @brief Minimum value for unsigned size type (16-bit)
 */
#            define EYA_USIZE_T_MIN EYA_U16_T_MIN
#        endif

#        ifndef EYA_USIZE_T_MAX
/**
 * @def EYA_USIZE_T_MAX
 * @brief Maximum value for unsigned size type (16-bit)
 */
#            define EYA_USIZE_T_MAX EYA_U16_T_MAX
#        endif

/**
 * @typedef eya_usize_t
 * @brief Unsigned 16-bit integer type for representing sizes or counts
 */
typedef eya_u16_t eya_usize_t;

#    elif EYA_SIZE_T_SIZE == 1
#        ifndef EYA_SSIZE_T_MIN
/**
 * @def EYA_SSIZE_T_MIN
 * @brief Minimum value for signed size type (8-bit)
 */
#            define EYA_SSIZE_T_MIN EYA_S8_T_MIN
#        endif

#        ifndef EYA_SSIZE_T_MAX
/**
 * @def EYA_SSIZE_T_MAX
 * @brief Maximum value for signed size type (8-bit)
 */
#            define EYA_SSIZE_T_MAX EYA_S8_T_MAX
#        endif

/**
 * @typedef eya_ssize_t
 * @brief Signed 8-bit integer type for representing sizes or counts
 */
typedef eya_s8_t eya_ssize_t;

#        ifndef EYA_USIZE_T_MIN
/**
 * @def EYA_USIZE_T_MIN
 * @brief Minimum value for unsigned size type (8-bit)
 */
#            define EYA_USIZE_T_MIN EYA_U8_T_MIN
#        endif

#        ifndef EYA_USIZE_T_MAX
/**
 * @def EYA_USIZE_T_MAX
 * @brief Maximum value for unsigned size type (8-bit)
 */
#            define EYA_USIZE_T_MAX EYA_U8_T_MAX
#        endif

/**
 * @typedef eya_usize_t
 * @brief Unsigned 8-bit integer type for representing sizes or counts
 */
typedef eya_u8_t eya_usize_t;
#    endif
#endif // EYA_SIZE_T_SIZE

#endif // EYA_SIZE_H