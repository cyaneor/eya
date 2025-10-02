/**
 * @file numeric_interval.h
 * @brief Predefined numeric interval constants.
 *
 * This header defines a set of constant intervals for all numeric type aliases.
 * Each interval consists of interval bounds (lower and upper) and interval flags.
 * By default, all intervals use @ref EYA_INTERVAL_FLAGS_CLOSED.
 *
 * Defined constants:
 * - `EYA_UCHAR_INTERVAL`  → interval for `unsigned char`
 * - `EYA_USHORT_INTERVAL` → interval for `unsigned short`
 * - `EYA_UINT_INTERVAL`   → interval for `unsigned int`
 * - `EYA_ULONG_INTERVAL`  → interval for `unsigned long`
 * - `EYA_ULLONG_INTERVAL` → interval for `unsigned long long`
 * - `EYA_SCHAR_INTERVAL`  → interval for `signed char`
 * - `EYA_SSHORT_INTERVAL` → interval for `signed short`
 * - `EYA_SINT_INTERVAL`   → interval for `signed int`
 * - `EYA_SLONG_INTERVAL`  → interval for `signed long`
 * - `EYA_SLLONG_INTERVAL` → interval for `signed long long`
 *
 * Example usage:
 * @code
 * if (value >= EYA_UINT_INTERVAL.bounds.lower &&
 *     value <= EYA_UINT_INTERVAL.bounds.upper) {
 *     // value is within the closed interval for unsigned int
 * }
 * @endcode
 *
 * @see numeric_interval_bounds.h
 * @see numeric_interval_types.h
 * @see EYA_INTERVAL_FLAGS_CLOSED
 */

#ifndef EYA_NUMERIC_INTERVAL_H
#define EYA_NUMERIC_INTERVAL_H

#include <eya/numeric_interval_bounds.h>
#include <eya/numeric_interval_types.h>

/** Closed interval for `unsigned char`. */
static const eya_uchar_interval EYA_UCHAR_INTERVAL = {EYA_UCHAR_INTERVAL_BOUNDS,
                                                      EYA_INTERVAL_FLAGS_CLOSED};

/** Closed interval for `unsigned short`. */
static const eya_ushort_interval EYA_USHORT_INTERVAL = {EYA_USHORT_INTERVAL_BOUNDS,
                                                        EYA_INTERVAL_FLAGS_CLOSED};

/** Closed interval for `unsigned int`. */
static const eya_uint_interval EYA_UINT_INTERVAL = {EYA_UINT_INTERVAL_BOUNDS,
                                                    EYA_INTERVAL_FLAGS_CLOSED};

/** Closed interval for `unsigned long`. */
static const eya_ulong_interval EYA_ULONG_INTERVAL = {EYA_ULONG_INTERVAL_BOUNDS,
                                                      EYA_INTERVAL_FLAGS_CLOSED};

/** Closed interval for `unsigned long long`. */
static const eya_ullong_interval EYA_ULLONG_INTERVAL = {EYA_ULLONG_INTERVAL_BOUNDS,
                                                        EYA_INTERVAL_FLAGS_CLOSED};

/** Closed interval for `signed char`. */
static const eya_schar_interval EYA_SCHAR_INTERVAL = {EYA_SCHAR_INTERVAL_BOUNDS,
                                                      EYA_INTERVAL_FLAGS_CLOSED};

/** Closed interval for `signed short`. */
static const eya_sshort_interval EYA_SSHORT_INTERVAL = {EYA_SSHORT_INTERVAL_BOUNDS,
                                                        EYA_INTERVAL_FLAGS_CLOSED};

/** Closed interval for `signed int`. */
static const eya_sint_interval EYA_SINT_INTERVAL = {EYA_SINT_INTERVAL_BOUNDS,
                                                    EYA_INTERVAL_FLAGS_CLOSED};

/** Closed interval for `signed long`. */
static const eya_slong_interval EYA_SLONG_INTERVAL = {EYA_SLONG_INTERVAL_BOUNDS,
                                                      EYA_INTERVAL_FLAGS_CLOSED};

/** Closed interval for `signed long long`. */
static const eya_sllong_interval EYA_SLLONG_INTERVAL = {EYA_SLLONG_INTERVAL_BOUNDS,
                                                        EYA_INTERVAL_FLAGS_CLOSED};

#endif // EYA_NUMERIC_INTERVAL_H
