/**
 * @file interval_bounds_fields.h
 * @brief Macro definition for declaring interval bounds structure fields.
 *
 * This header provides the `eya_interval_bounds_fields(T)` macro,
 * which expands to two fields `lower` and `upper` of type `T`.
 */

#ifndef EYA_INTERVAL_BOUNDS_FIELDS_H
#define EYA_INTERVAL_BOUNDS_FIELDS_H

/**
 * @def eya_interval_bounds_fields(T)
 * @brief Defines the fields of an interval bounds structure.
 *
 * This macro expands to two fields, `lower` and `upper`, both of type `T`.
 * It is intended to be used inside a structure definition to represent
 * the lower and upper bounds of an interval.
 *
 * Example usage:
 * @code
 * typedef struct {
 *     eya_interval_bounds_fields(int);
 * } int_interval_t;
 *
 * int_interval_t range = { .lower = 0, .upper = 10 };
 * @endcode
 *
 * @param T The type of the lower and upper bounds.
 */
#define eya_interval_bounds_fields(T)                                                              \
    T lower;                                                                                       \
    T upper

#endif // EYA_INTERVAL_BOUNDS_FIELDS_H
