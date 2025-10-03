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
 * - `flags`: interval boundary flags, using `eya_interval_flags_t`.
 *
 * @note `T` is expected to be a structure created using the interval bounds macros
 *       (`eya_interval_bounds_struct` or `eya_interval_bounds_type`) which contains
 *       `lower` and `upper` fields.
 */

#ifndef EYA_INTERVAL_FIELDS_H
#define EYA_INTERVAL_FIELDS_H

#include <eya/interval_flags.h>

/**
 * @def eya_interval_fields(T)
 * @brief Defines the common fields for an interval structure.
 *
 * Expands to:
 * - A `bounds` field of type `T`, which holds the lower and upper bounds.
 * - A `flags` field of type `eya_interval_flags_t`, indicating the interval's openness.
 *
 * @param T Structure type containing the interval bounds, typically created using
 *          `eya_interval_bounds_struct(T, Name)` or `eya_interval_bounds_type(T, Name)`.
 *
 * Example usage:
 * @code
 * typedef struct my_bounds {
 *     double lower;
 *     double upper;
 * } my_bounds_t;
 *
 * struct my_interval {
 *     eya_interval_fields(my_bounds_t)
 * };
 *
 * // Access example:
 * struct my_interval interval;
 * interval.bounds.lower = 0.0;
 * interval.bounds.upper = 1.0;
 * interval.flags = EYA_INTERVAL_FLAGS_OPEN_RIGHT;
 * @endcode
 */
#define eya_interval_fields(T)                                                                     \
    T                    bounds;                                                                   \
    eya_interval_flags_t flags

#endif // EYA_INTERVAL_FIELDS_H
