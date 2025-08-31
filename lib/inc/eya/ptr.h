/**
 * @file ptr.h
 * @brief Pointer type definitions and limits
 *
 * This header defines platform-specific pointer types and their size/limit constants.
 * The implementation depends on whether EYA_VOID_P_SIZE is defined by the platform.
 */

#ifndef EYA_PTR_H
#define EYA_PTR_H

#include "numeric_limit.h"

#ifdef EYA_VOID_P_SIZE
/**
 * @def EYA_PTR_SIZE
 * @brief Size identifier for pointer type
 * @details Uses platform-defined EYA_VOID_P_SIZE constant
 */
#    define EYA_PTR_SIZE EYA_VOID_P_SIZE

/**
 * @def EYA_PTR_MIN
 * @brief Minimum value for pointer type
 * @details Uses eya_numeric_limit_umin() function with eya_ptr_t type
 */
#    define EYA_PTR_MIN eya_numeric_limit_umin(eya_ptr_t)

/**
 * @def EYA_PTR_MAX
 * @brief Maximum value for pointer type
 * @details Uses eya_numeric_limit_umax() function with eya_ptr_t type
 */
#    define EYA_PTR_MAX eya_numeric_limit_umax(eya_ptr_t)

/**
 * @typedef eya_ptr_t
 * @brief Platform's native pointer type
 * @details Defined as void* when EYA_VOID_P_SIZE is available
 */
#    define eya_ptr_t void *

#else /* EYA_VOID_P_SIZE not defined */
/**
 * @brief Compilation error for unsupported platforms
 * @details Generates error if platform doesn't define EYA_VOID_P_SIZE
 */
#    error "Pointer size not defined for this platform (EYA_VOID_P_SIZE undefined)"

#endif /* EYA_VOID_P_SIZE */

#endif /* EYA_PTR_H */