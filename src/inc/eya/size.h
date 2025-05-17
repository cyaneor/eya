/**
 * @file size.h
 * @brief Header file defining signed
 *        and unsigned size types (`eya_ssize_t` and `eya_usize_t`).
 *
 * This file provides definitions for `eya_ssize_t` and `eya_usize_t` types,
 * along with their minimum and maximum values based on the size specified
 * by the `EYA_SIZE_T_SIZE` macro.
 */

#ifndef EYA_SIZE_H
#define EYA_SIZE_H

#include "numeric_fixed.h"

#ifdef EYA_SIZE_T_SIZE
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