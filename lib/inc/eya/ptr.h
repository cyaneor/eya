/**
 * @file ptr.h
 * @brief Pointer type definitions and limits
 *
 * This header defines platform-specific pointer types and their size/limit constants.
 * The implementation uses EYA_VOID_P_SIZE if defined externally, otherwise falls back
 * to automatic size detection.
 */

#ifndef EYA_PTR_H
#define EYA_PTR_H

#include "reinterpret_cast.h"
#include "type_util.h"

/**
 * @def EYA_PTR_T_SIZE
 * @brief Size identifier for pointer type
 *
 * If EYA_VOID_P_SIZE is defined externally, uses that value.
 * Otherwise defaults to sizeof(eya_ptr_t) for automatic size detection.
 */
#ifndef EYA_PTR_T_SIZE
#    define EYA_PTR_T_SIZE eya_type_size(eya_ptr_t)
#endif /* EYA_VOID_P_SIZE */

/**
 * @def EYA_PTR_T_MIN
 * @brief Minimum value for pointer type
 * * Represents the minimum valid pointer value (typically null pointer).
 * Uses reinterpret casting to ensure proper type conversion.
 */
#ifndef EYA_PTR_T_MIN
#    define EYA_PTR_T_MIN eya_type_zero_v(eya_ptr_t)
#endif // EYA_PTR_T_MIN

/**
 * @def EYA_PTR_T_MAX
 * @brief Maximum value for pointer type
 *
 * Represents the maximum valid pointer value for the platform.
 * Uses reinterpret casting of -1 to get the maximum unsigned pointer value.
 */
#ifndef EYA_PTR_T_MAX
#    define EYA_PTR_T_MAX eya_reinterpret_cast(eya_ptr_t, -1)
#endif // EYA_PTR_T_MAX

/**
 * @typedef eya_ptr_t
 * @brief Platform's native pointer type
 *
 * Defines the standard pointer type for the platform, typically void*.
 * Used for consistent pointer handling across different architectures.
 */
#define eya_ptr_t void *

#endif /* EYA_PTR_H */