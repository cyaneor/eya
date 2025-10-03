/**
 * @file addr.h
 * @brief Definition of types and limits for addresses based on pointer size
 *
 * This code defines unsigned (`eya_uaddr_t`) and signed (`eya_saddr_t`) address types,
 * along with their minimum values, maximum values, and size in bytes based on
 * the `EYA_PTR_T_SIZE` macro value.
 */

#ifndef EYA_ADDR_H
#define EYA_ADDR_H

#include <eya/numeric_types.h>
#include <eya/numeric_limits.h>

#ifdef EYA_PTR_T_SIZE
#    if EYA_PTR_T_SIZE == 8

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
typedef eya_ullong_t eya_uaddr_t;

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
typedef eya_sllong_t eya_saddr_t;

#    elif EYA_PTR_T_SIZE == 4

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
typedef eya_uint_t eya_uaddr_t;

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
typedef eya_sint_t eya_saddr_t;

#    elif EYA_PTR_T_SIZE == 2

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
typedef eya_ushort_t eya_uaddr_t;

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
typedef eya_sshort_t eya_saddr_t;

#    elif EYA_PTR_T_SIZE == 1

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
typedef eya_uchar_t eya_uaddr_t;

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
typedef eya_schar_t eya_saddr_t;

#    else
#        error "Unsupported pointer size EYA_PTR_T_SIZE"
#    endif
#else
#    error "EYA_PTR_T_SIZE is not defined"
#endif

#endif /* EYA_ADDR_H */