/**
 * @file addr.h
 * @brief Definition of types and limits for addresses based on pointer size
 *
 * This code defines unsigned (`eya_uaddr_t`) and signed (`eya_saddr_t`) address types,
 * along with their minimum values, maximum values, and size in bytes based on
 * the `EYA_VOID_P_SIZE` macro value.
 */

#ifndef EYA_ADDR_H
#define EYA_ADDR_H

#include "numeric_fixed.h"

#ifdef EYA_VOID_P_SIZE
#    if EYA_VOID_P_SIZE == 8

#        ifndef EYA_UADDR_T_MIN
/**
 * @def EYA_UADDR_T_MIN
 * @brief Minimum value for unsigned address type in 64-bit systems
 */
#            define EYA_UADDR_T_MIN EYA_U64_T_MIN
#        endif // EYA_UADDR_T_MIN

#        ifndef EYA_UADDR_T_MAX
/**
 * @def EYA_UADDR_T_MAX
 * @brief Maximum value for unsigned address type in 64-bit systems
 */
#            define EYA_UADDR_T_MAX EYA_U64_T_MAX
#        endif // EYA_UADDR_T_MAX

#        ifndef EYA_UADDR_T_SIZE
/**
 * @def EYA_UADDR_T_SIZE
 * @brief Size of unsigned address type in bytes for 64-bit systems
 */
#            define EYA_UADDR_T_SIZE EYA_U64_T_SIZE
#        endif // EYA_UADDR_T_SIZE

/**
 * @typedef eya_uaddr_t
 * @brief Unsigned address type for 64-bit systems
 */
typedef eya_u64_t eya_uaddr_t;

#        ifndef EYA_SADDR_T_MIN
/**
 * @def EYA_SADDR_T_MIN
 * @brief Minimum value for signed address type in 64-bit systems
 */
#            define EYA_SADDR_T_MIN EYA_S64_T_MIN
#        endif // EYA_SADDR_T_MIN

#        ifndef EYA_SADDR_T_MAX
/**
 * @def EYA_SADDR_T_MAX
 * @brief Maximum value for signed address type in 64-bit systems
 */
#            define EYA_SADDR_T_MAX EYA_S64_T_MAX
#        endif // EYA_SADDR_T_MAX

#        ifndef EYA_SADDR_T_SIZE
/**
 * @def EYA_SADDR_T_SIZE
 * @brief Size of signed address type in bytes for 64-bit systems
 */
#            define EYA_SADDR_T_SIZE EYA_S64_T_SIZE
#        endif // EYA_SADDR_T_SIZE

/**
 * @typedef eya_saddr_t
 * @brief Signed address type for 64-bit systems
 */
typedef eya_s64_t eya_saddr_t;

#    elif EYA_VOID_P_SIZE == 4

#        ifndef EYA_UADDR_T_MIN
/**
 * @def EYA_UADDR_T_MIN
 * @brief Minimum value for unsigned address type in 32-bit systems
 */
#            define EYA_UADDR_T_MIN EYA_U32_T_MIN
#        endif // EYA_UADDR_T_MIN

#        ifndef EYA_UADDR_T_MAX
/**
 * @def EYA_UADDR_T_MAX
 * @brief Maximum value for unsigned address type in 32-bit systems
 */
#            define EYA_UADDR_T_MAX EYA_U32_T_MAX
#        endif // EYA_UADDR_T_MAX

#        ifndef EYA_UADDR_T_SIZE
/**
 * @def EYA_UADDR_T_SIZE
 * @brief Size of unsigned address type in bytes for 32-bit systems
 */
#            define EYA_UADDR_T_SIZE EYA_U32_T_SIZE
#        endif // EYA_UADDR_T_SIZE

/**
 * @typedef eya_uaddr_t
 * @brief Unsigned address type for 32-bit systems
 */
typedef eya_u32_t eya_uaddr_t;

#        ifndef EYA_SADDR_T_MIN
/**
 * @def EYA_SADDR_T_MIN
 * @brief Minimum value for signed address type in 32-bit systems
 */
#            define EYA_SADDR_T_MIN EYA_S32_T_MIN
#        endif // EYA_SADDR_T_MIN

#        ifndef EYA_SADDR_T_MAX
/**
 * @def EYA_SADDR_T_MAX
 * @brief Maximum value for signed address type in 32-bit systems
 */
#            define EYA_SADDR_T_MAX EYA_S32_T_MAX
#        endif // EYA_SADDR_T_MAX

#        ifndef EYA_SADDR_T_SIZE
/**
 * @def EYA_SADDR_T_SIZE
 * @brief Size of signed address type in bytes for 32-bit systems
 */
#            define EYA_SADDR_T_SIZE EYA_S32_T_SIZE
#        endif // EYA_SADDR_T_SIZE

/**
 * @typedef eya_saddr_t
 * @brief Signed address type for 32-bit systems
 */
typedef eya_s32_t eya_saddr_t;

#    elif EYA_VOID_P_SIZE == 2

#        ifndef EYA_UADDR_T_MIN
/**
 * @def EYA_UADDR_T_MIN
 * @brief Minimum value for unsigned address type in 16-bit systems
 */
#            define EYA_UADDR_T_MIN EYA_U16_T_MIN
#        endif // EYA_UADDR_T_MIN

#        ifndef EYA_UADDR_T_MAX
/**
 * @def EYA_UADDR_T_MAX
 * @brief Maximum value for unsigned address type in 16-bit systems
 */
#            define EYA_UADDR_T_MAX EYA_U16_T_MAX
#        endif // EYA_UADDR_T_MAX

#        ifndef EYA_UADDR_T_SIZE
/**
 * @def EYA_UADDR_T_SIZE
 * @brief Size of unsigned address type in bytes for 16-bit systems
 */
#            define EYA_UADDR_T_SIZE EYA_U16_T_SIZE
#        endif // EYA_UADDR_T_SIZE

/**
 * @typedef eya_uaddr_t
 * @brief Unsigned address type for 16-bit systems
 */
typedef eya_u16_t eya_uaddr_t;

#        ifndef EYA_SADDR_T_MIN
/**
 * @def EYA_SADDR_T_MIN
 * @brief Minimum value for signed address type in 16-bit systems
 */
#            define EYA_SADDR_T_MIN EYA_S16_T_MIN
#        endif // EYA_SADDR_T_MIN

#        ifndef EYA_SADDR_T_MAX
/**
 * @def EYA_SADDR_T_MAX
 * @brief Maximum value for signed address type in 16-bit systems
 */
#            define EYA_SADDR_T_MAX EYA_S16_T_MAX
#        endif // EYA_SADDR_T_MAX

#        ifndef EYA_SADDR_T_SIZE
/**
 * @def EYA_SADDR_T_SIZE
 * @brief Size of signed address type in bytes for 16-bit systems
 */
#            define EYA_SADDR_T_SIZE EYA_S16_T_SIZE
#        endif // EYA_SADDR_T_SIZE

/**
 * @typedef eya_saddr_t
 * @brief Signed address type for 16-bit systems
 */
typedef eya_s16_t eya_saddr_t;

#    elif EYA_VOID_P_SIZE == 1

#        ifndef EYA_UADDR_T_MIN
/**
 * @def EYA_UADDR_T_MIN
 * @brief Minimum value for unsigned address type in 8-bit systems
 */
#            define EYA_UADDR_T_MIN EYA_U8_T_MIN
#        endif // EYA_UADDR_T_MIN

#        ifndef EYA_UADDR_T_MAX
/**
 * @def EYA_UADDR_T_MAX
 * @brief Maximum value for unsigned address type in 8-bit systems
 */
#            define EYA_UADDR_T_MAX EYA_U8_T_MAX
#        endif // EYA_UADDR_T_MAX

#        ifndef EYA_UADDR_T_SIZE
/**
 * @def EYA_UADDR_T_SIZE
 * @brief Size of unsigned address type in bytes for 8-bit systems
 */
#            define EYA_UADDR_T_SIZE EYA_U8_T_SIZE
#        endif // EYA_UADDR_T_SIZE

/**
 * @typedef eya_uaddr_t
 * @brief Unsigned address type for 8-bit systems
 */
typedef eya_u8_t eya_uaddr_t;

#        ifndef EYA_SADDR_T_MIN
/**
 * @def EYA_SADDR_T_MIN
 * @brief Minimum value for signed address type in 8-bit systems
 */
#            define EYA_SADDR_T_MIN EYA_S8_T_MIN
#        endif // EYA_SADDR_T_MIN

#        ifndef EYA_SADDR_T_MAX
/**
 * @def EYA_SADDR_T_MAX
 * @brief Maximum value for signed address type in 8-bit systems
 */
#            define EYA_SADDR_T_MAX EYA_S8_T_MAX
#        endif // EYA_SADDR_T_MAX

#        ifndef EYA_SADDR_T_SIZE
/**
 * @def EYA_SADDR_T_SIZE
 * @brief Size of signed address type in bytes for 8-bit systems
 */
#            define EYA_SADDR_T_SIZE EYA_S8_T_SIZE
#        endif // EYA_SADDR_T_SIZE

/**
 * @typedef eya_saddr_t
 * @brief Signed address type for 8-bit systems
 */
typedef eya_s8_t eya_saddr_t;

#    else
#        error "Unsupported pointer size EYA_VOID_P_SIZE"
#    endif
#else
#    error "EYA_VOID_P_SIZE is not defined"
#endif

#endif /* EYA_ADDR_H */