/**
 * @file numeric_interval_bounds_types.h
 * @brief Predefined interval bounds types for numeric aliases.
 *
 * This header defines a set of typedefs for interval bounds structures
 * corresponding to numeric type aliases defined in @ref numeric_types.h.
 * Each typedef represents an interval with `lower` and `upper` fields
 * of the corresponding numeric type.
 *
 * These typedefs are generated using the @ref eya_interval_bounds_type macro
 * from @ref interval_bounds_struct.h.
 *
 * Defined types:
 * - `eya_uchar_interval_bounds`   → interval bounds for `unsigned char`
 * - `eya_ushort_interval_bounds`  → interval bounds for `unsigned short`
 * - `eya_uint_interval_bounds`    → interval bounds for `unsigned int`
 * - `eya_ulong_interval_bounds`   → interval bounds for `unsigned long`
 * - `eya_ullong_interval_bounds`  → interval bounds for `unsigned long long`
 * - `eya_schar_interval_bounds`   → interval bounds for `signed char`
 * - `eya_sshort_interval_bounds`  → interval bounds for `signed short`
 * - `eya_sint_interval_bounds`    → interval bounds for `signed int`
 * - `eya_slong_interval_bounds`   → interval bounds for `signed long`
 * - `eya_sllong_interval_bounds`  → interval bounds for `signed long long`
 *
 * Example usage:
 * @code
 * eya_uint_interval_bounds range;
 * range.lower = 10;
 * range.upper = 100;
 * if (value >= range.lower && value <= range.upper) {
 *     // value is within the interval
 * }
 * @endcode
 *
 * @see eya_interval_bounds_struct
 * @see eya_interval_bounds_type
 * @see numeric_types.h
 */

#ifndef EYA_NUMERIC_INTERVAL_BOUNDS_TYPES_H
#define EYA_NUMERIC_INTERVAL_BOUNDS_TYPES_H

#include <eya/interval_bounds_struct.h>
#include <eya/numeric_types.h>

/** Interval bounds typedef for `unsigned char`. */
eya_interval_bounds_type(eya_uchar_t, eya_uchar_interval_bounds);

/** Interval bounds typedef for `unsigned short`. */
eya_interval_bounds_type(eya_ushort_t, eya_ushort_interval_bounds);

/** Interval bounds typedef for `unsigned int`. */
eya_interval_bounds_type(eya_uint_t, eya_uint_interval_bounds);

/** Interval bounds typedef for `unsigned long`. */
eya_interval_bounds_type(eya_ulong_t, eya_ulong_interval_bounds);

/** Interval bounds typedef for `unsigned long long`. */
eya_interval_bounds_type(eya_ullong_t, eya_ullong_interval_bounds);

/** Interval bounds typedef for `signed char`. */
eya_interval_bounds_type(eya_schar_t, eya_schar_interval_bounds);

/** Interval bounds typedef for `signed short`. */
eya_interval_bounds_type(eya_sshort_t, eya_sshort_interval_bounds);

/** Interval bounds typedef for `signed int`. */
eya_interval_bounds_type(eya_sint_t, eya_sint_interval_bounds);

/** Interval bounds typedef for `signed long`. */
eya_interval_bounds_type(eya_slong_t, eya_slong_interval_bounds);

/** Interval bounds typedef for `signed long long`. */
eya_interval_bounds_type(eya_sllong_t, eya_sllong_interval_bounds);

#endif // EYA_NUMERIC_INTERVAL_BOUNDS_TYPES_H
