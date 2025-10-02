/**
 * @file interval_fields.h
 * @brief Defines the fields for an interval structure.
 *
 * This header provides a macro `eya_interval_fields(T)`
 * to define the common fields of an interval structure.
 *
 * The macro is designed to be used with structures representing interval bounds,
 * typically defined via `eya_interval_bounds_struct(T, Name)`
 * or `eya_interval_bounds_type(T, Name)`.
 *
 * The resulting structure contains:
 * - `bounds`: the lower and upper bounds of the interval, defined by the type `T`.
 * - `type`: the type of interval, using `eya_interval_type`.
 *
 * @note `T` is expected to be a structure created using the interval bounds macros
 *       (`eya_interval_bounds_struct` or `eya_interval_bounds_type`) which contains
 *       `lower` and `upper` fields.
 */

#ifndef EYA_INTERVAL_FIELDS_H
#define EYA_INTERVAL_FIELDS_H

#include <eya/interval_type.h>

/**
 * @def eya_interval_fields(T)
 * @brief Defines the common fields for an interval structure.
 *
 * Expands to:
 * - A `bounds` field of type `T`, which holds the lower and upper bounds.
 * - A `type` field of type `eya_interval_type`, indicating the interval's type.
 *
 * @param T Structure type containing the interval bounds, typically created using
 *          `eya_interval_bounds_struct(T, Name)` or `eya_interval_bounds_type(T, Name)`.
 *
 * @code
 * // Example usage:
 * typedef struct my_bounds {
 *     double lower;
 *     double upper;
 * } my_bounds_t;
 *
 * struct my_interval {
 *     eya_interval_fields(my_bounds_t)
 * };
 * @endcode
 */
#define eya_interval_fields(T)                                                                     \
    T                 bounds;                                                                      \
    eya_interval_type type;

#endif // EYA_INTERVAL_FIELDS_H
