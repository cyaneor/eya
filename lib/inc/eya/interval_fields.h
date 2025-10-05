/**
 * @file interval_fields.h
 * @brief Macro for defining interval fields with bounds and flags.
 *
 * This header provides a macro to define the fields for an interval structure,
 * including the bounds and the interval flags that specify boundary openness.
 * The macro is designed to be used with different types for the bounds.
 *
 * @see interval_flags.h for details on the interval flags.
 */

#ifndef EYA_INTERVAL_FIELDS_H
#define EYA_INTERVAL_FIELDS_H

#include <eya/interval_flags.h>

/**
 * @def eya_interval_fields(T)
 * @brief Macro to define interval fields.
 * @param T The type of the interval bounds (e.g., int, double, float).
 * @details Expands to define two fields:
 *          - `bounds` of type `T` to store the interval boundaries.
 *          - `flags` of type `eya_interval_flags_t` to store boundary openness flags.
 *
 * @note The `bounds` field typically represents the lower and upper limits of the interval,
 *       while `flags` indicates whether the boundaries are open or closed.
 *
 * @see eya_interval_flags_t for flag definitions.
 */
#define eya_interval_fields(T)                                                                     \
    T                    bounds;                                                                   \
    eya_interval_flags_t flags

#endif // EYA_INTERVAL_FIELDS_H