/**
 * @file interval_struct.h
 * @brief Macros for defining interval structures and typedefs.
 *
 * This header provides macros for defining interval structures that include
 * both interval bounds and the interval type. It builds on `eya_interval_fields(T)`,
 * which provides the common fields of an interval structure.
 *
 * The resulting structures have:
 * - `bounds`: lower and upper bounds of the interval (of type `T`).
 * - `type`: interval type (`eya_interval_type`).
 */

#ifndef EYA_INTERVAL_STRUCT_H
#define EYA_INTERVAL_STRUCT_H

#include <eya/interval_fields.h>

/**
 * @def eya_interval_struct(T, ...)
 * @brief Defines a structure representing an interval.
 *
 * Expands into a `struct` with fields defined by `eya_interval_fields(T)`:
 * - `bounds` of type `T` (contains `lower` and `upper`).
 * - `type` of type `eya_interval_type`.
 *
 * @param T Type of the interval bounds structure (created using
 *          `eya_interval_bounds_struct` or `eya_interval_bounds_type`).
 * @param ... Name of the structure being defined.
 *
 * @code
 * // Example usage:
 * typedef struct my_bounds {
 *     double lower;
 *     double upper;
 * } my_bounds_t;
 *
 * eya_interval_struct(my_bounds_t, my_interval_t);
 *
 * struct my_interval_t interval_instance;
 * interval_instance.bounds.lower = 0.0;
 * interval_instance.bounds.upper = 1.0;
 * interval_instance.type = EYA_INTERVAL_CLOSED;
 * @endcode
 */
#define eya_interval_struct(T, ...)                                                                \
    struct __VA_ARGS__                                                                             \
    {                                                                                              \
        eya_interval_fields(T);                                                                    \
    }

/**
 * @def eya_interval_type(T, ...)
 * @brief Defines a typedef for an interval structure.
 *
 * Creates a typedef for a structure defined by `eya_interval_struct(T, ...)`.
 *
 * @param T Type of the interval bounds structure (created using
 *          `eya_interval_bounds_struct` or `eya_interval_bounds_type`).
 * @param ... Name of the typedef to create.
 *
 * Example usage:
 * @code
 * // Example usage:
 * typedef struct my_bounds {
 *     double lower;
 *     double upper;
 * } my_bounds_t;
 *
 * eya_interval_type(my_bounds_t, my_interval_t);
 *
 * my_interval_t interval_instance;
 * interval_instance.bounds.lower = 0.0;
 * interval_instance.bounds.upper = 1.0;
 * interval_instance.type = EYA_INTERVAL_CLOSED;
 * @endcode
 */
#define eya_interval_type(T, ...) typedef eya_interval_struct(T, __VA_ARGS__) __VA_ARGS__

#endif // EYA_INTERVAL_STRUCT_H
