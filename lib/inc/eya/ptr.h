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

/**
 * @def EYA_PTR_SIZE
 * @brief Size identifier for pointer type
 */
#ifndef EYA_PTR_T_SIZE
#    define EYA_PTR_T_SIZE eya_type_size(eya_ptr_t)
#endif /* EYA_VOID_P_SIZE */

/**
 * @def EYA_PTR_MIN
 * @brief Minimum value for pointer type
 * @details Uses eya_numeric_limit_umin() function with eya_ptr_t type
 */
#ifndef EYA_PTR_T_MIN
#    define EYA_PTR_T_MIN eya_numeric_limit_umin(eya_ptr_t)
#endif // EYA_PTR_T_MIN

/**
 * @def EYA_PTR_MAX
 * @brief Maximum value for pointer type
 * @details Uses eya_numeric_limit_umax() function with eya_ptr_t type
 */
#ifndef EYA_PTR_T_MAX
#    define EYA_PTR_T_MAX eya_numeric_limit_umax(eya_ptr_t)
#endif // EYA_PTR_T_MAX

/**
 * @typedef eya_ptr_t
 * @brief Platform's native pointer type
 */
#define eya_ptr_t void *

#endif /* EYA_PTR_H */