/**
 * @file interval_bounds_struct.h
 * @brief Macros for defining interval bounds structures and typedefs.
 *
 * This header provides helper macros for defining structures that represent
 * interval bounds with `lower` and `upper` fields of a given type.
 * It builds on the `eya_interval_bounds_fields(T)` macro.
 */

#ifndef EYA_INTERVAL_BOUNDS_STRUCT_H
#define EYA_INTERVAL_BOUNDS_STRUCT_H

#include <eya/interval_bounds_fields.h>

/**
 * @def eya_interval_bounds_struct(T, ...)
 * @brief Defines a structure with lower and upper bounds of type `T`.
 *
 * Expands into a structure definition with fields `lower` and `upper` of type `T`.
 * The variadic argument `__VA_ARGS__` is used as the structure name.
 *
 * @param T The type of the interval bounds.
 * @param ... The structure name.
 */
#define eya_interval_bounds_struct(T, ...)                                                         \
    struct __VA_ARGS__                                                                             \
    {                                                                                              \
        eya_interval_bounds_fields(T);                                                             \
    }

/**
 * @def eya_interval_bounds_type(T, ...)
 * @brief Defines a typedef for an interval bounds structure.
 *
 * Creates a typedef for a structure with fields `lower` and `upper` of type `T`.
 * The variadic argument `__VA_ARGS__` specifies the typedef name.
 *
 * @param T The type of the interval bounds.
 * @param ... The typedef name.
 */
#define eya_interval_bounds_type(T, ...) typedef eya_interval_bounds_struct(T) __VA_ARGS__

#endif // EYA_INTERVAL_BOUNDS_STRUCT_H
