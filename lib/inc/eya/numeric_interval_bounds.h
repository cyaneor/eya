/**
 * @file numeric_interval_bounds.h
 * @brief Predefined interval bounds constants for numeric aliases.
 *
 * This header defines a set of constant interval bounds for all numeric type aliases
 * provided in @ref numeric_interval_bounds_types.h. Each constant represents the
 * minimum and maximum values for a specific numeric type.
 *
 * These constants are useful for validation, range checks, and safe numeric operations.
 *
 * Defined constants:
 * - `EYA_UCHAR_INTERVAL_BOUNDS`  → interval bounds for `unsigned char`
 * - `EYA_USHORT_INTERVAL_BOUNDS` → interval bounds for `unsigned short`
 * - `EYA_UINT_INTERVAL_BOUNDS`   → interval bounds for `unsigned int`
 * - `EYA_ULONG_INTERVAL_BOUNDS`  → interval bounds for `unsigned long`
 * - `EYA_ULLONG_INTERVAL_BOUNDS` → interval bounds for `unsigned long long`
 * - `EYA_SCHAR_INTERVAL_BOUNDS`  → interval bounds for `signed char`
 * - `EYA_SSHORT_INTERVAL_BOUNDS` → interval bounds for `signed short`
 * - `EYA_SINT_INTERVAL_BOUNDS`   → interval bounds for `signed int`
 * - `EYA_SLONG_INTERVAL_BOUNDS`  → interval bounds for `signed long`
 * - `EYA_SLLONG_INTERVAL_BOUNDS` → interval bounds for `signed long long`
 *
 * Example usage:
 * @code
 * if (value >= EYA_UINT_INTERVAL_BOUNDS.lower &&
 *     value <= EYA_UINT_INTERVAL_BOUNDS.upper) {
 *     // value is within the allowed range for unsigned int
 * }
 * @endcode
 *
 * @see eya_numeric_limit
 * @see numeric_interval_bounds_types.h
 */

#ifndef EYA_NUMERIC_INTERVAL_BOUNDS_H
#define EYA_NUMERIC_INTERVAL_BOUNDS_H

#include <eya/numeric_interval_bounds_types.h>
#include <eya/numeric_limit.h>

/** Interval bounds for `unsigned char`. */
static const eya_uchar_interval_bounds EYA_UCHAR_INTERVAL_BOUNDS = {
    eya_numeric_limit_min(eya_uchar_t),
    eya_numeric_limit_max(eya_uchar_t)};

/** Interval bounds for `unsigned short`. */
static const eya_ushort_interval_bounds EYA_USHORT_INTERVAL_BOUNDS = {
    eya_numeric_limit_min(eya_ushort_t),
    eya_numeric_limit_max(eya_ushort_t)};

/** Interval bounds for `unsigned int`. */
static const eya_uint_interval_bounds EYA_UINT_INTERVAL_BOUNDS = {
    eya_numeric_limit_min(eya_uint_t),
    eya_numeric_limit_max(eya_uint_t)};

/** Interval bounds for `unsigned long`. */
static const eya_ulong_interval_bounds EYA_ULONG_INTERVAL_BOUNDS = {
    eya_numeric_limit_min(eya_ulong_t),
    eya_numeric_limit_max(eya_ulong_t)};

/** Interval bounds for `unsigned long long`. */
static const eya_ullong_interval_bounds EYA_ULLONG_INTERVAL_BOUNDS = {
    eya_numeric_limit_min(eya_ullong_t),
    eya_numeric_limit_max(eya_ullong_t)};

/** Interval bounds for `signed char`. */
static const eya_schar_interval_bounds EYA_SCHAR_INTERVAL_BOUNDS = {
    eya_numeric_limit_min(eya_schar_t),
    eya_numeric_limit_max(eya_schar_t)};

/** Interval bounds for `signed short`. */
static const eya_sshort_interval_bounds EYA_SSHORT_INTERVAL_BOUNDS = {
    eya_numeric_limit_min(eya_sshort_t),
    eya_numeric_limit_max(eya_sshort_t)};

/** Interval bounds for `signed int`. */
static const eya_sint_interval_bounds EYA_SINT_INTERVAL_BOUNDS = {
    eya_numeric_limit_min(eya_sint_t),
    eya_numeric_limit_max(eya_sint_t)};

/** Interval bounds for `signed long`. */
static const eya_slong_interval_bounds EYA_SLONG_INTERVAL_BOUNDS = {
    eya_numeric_limit_min(eya_slong_t),
    eya_numeric_limit_max(eya_slong_t)};

/** Interval bounds for `signed long long`. */
static const eya_sllong_interval_bounds EYA_SLLONG_INTERVAL_BOUNDS = {
    eya_numeric_limit_min(eya_sllong_t),
    eya_numeric_limit_max(eya_sllong_t)};

#endif // EYA_NUMERIC_INTERVAL_BOUNDS_H
