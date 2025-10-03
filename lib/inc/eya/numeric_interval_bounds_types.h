/**
 * @file numeric_interval_bounds_types.h
 * @brief Type definitions for interval bounds using custom numeric types.
 *
 * This header defines typedefs for interval bounds structures
 * for various custom numeric types defined in `numeric_types.h`.
 */

#ifndef EYA_NUMERIC_INTERVAL_BOUNDS_TYPES_H
#define EYA_NUMERIC_INTERVAL_BOUNDS_TYPES_H

#include <eya/interval_bounds_fields.h>
#include <eya/numeric_types.h>

/**
 * @struct eya_uchar_interval_bounds
 * @brief Interval bounds structure for unsigned char (8 bits).
 *
 * Defines a structure with `lower`
 * and `upper` fields of type `eya_uchar_t`.
 */
typedef struct eya_uchar_interval_bounds
{
    eya_interval_bounds_fields(eya_uchar_t);
} eya_uchar_interval_bounds_t;

/**
 * @struct eya_ushort_interval_bounds
 * @brief Interval bounds structure for unsigned short integer (typically 16 bits).
 *
 * Defines a structure with `lower`
 * and `upper` fields of type `eya_ushort_t`.
 */
typedef struct eya_ushort_interval_bounds
{
    eya_interval_bounds_fields(eya_ushort_t);
} eya_ushort_interval_bounds_t;

/**
 * @struct eya_uint_interval_bounds
 * @brief Interval bounds structure for unsigned integer (typically 32 bits).
 *
 * Defines a structure with `lower`
 * and `upper` fields of type `eya_uint_t`.
 */
typedef struct eya_uint_interval_bounds
{
    eya_interval_bounds_fields(eya_uint_t);
} eya_uint_interval_bounds_t;

/**
 * @struct eya_ulong_interval_bounds
 * @brief Interval bounds structure for unsigned long integer
 *        (typically 32 or 64 bits depending on platform).
 *
 * Defines a structure with `lower`
 * and `upper` fields of type `eya_ulong_t`.
 */
typedef struct eya_ulong_interval_bounds
{
    eya_interval_bounds_fields(eya_ulong_t);
} eya_ulong_interval_bounds_t;

/**
 * @struct eya_ullong_interval_bounds
 * @brief Interval bounds structure for unsigned long long integer (typically 64 bits).
 *
 * Defines a structure with `lower`
 * and `upper` fields of type `eya_ullong_t`.
 */
typedef struct eya_ullong_interval_bounds
{
    eya_interval_bounds_fields(eya_ullong_t);
} eya_ullong_interval_bounds_t;

/**
 * @struct eya_schar_interval_bounds
 * @brief Interval bounds structure for signed char (8 bits).
 *
 * Defines a structure with `lower`
 * and `upper` fields of type `eya_schar_t`.
 */
typedef struct eya_schar_interval_bounds
{
    eya_interval_bounds_fields(eya_schar_t);
} eya_schar_interval_bounds_t;

/**
 * @struct eya_sshort_interval_bounds
 * @brief Interval bounds structure for signed short integer (typically 16 bits).
 *
 * Defines a structure with `lower`
 * and `upper` fields of type `eya_sshort_t`.
 */
typedef struct eya_sshort_interval_bounds
{
    eya_interval_bounds_fields(eya_sshort_t);
} eya_sshort_interval_bounds_t;

/**
 * @struct eya_sint_interval_bounds
 * @brief Interval bounds structure for signed integer (typically 32 bits).
 *
 * Defines a structure with `lower`
 * and `upper` fields of type `eya_sint_t`.
 */
typedef struct eya_sint_interval_bounds
{
    eya_interval_bounds_fields(eya_sint_t);
} eya_sint_interval_bounds_t;

/**
 * @struct eya_slong_interval_bounds
 * @brief Interval bounds structure for signed long integer
 *        (typically 32 or 64 bits depending on platform).
 *
 * Defines a structure with `lower`
 * and `upper` fields of type `eya_slong_t`.
 */
typedef struct eya_slong_interval_bounds
{
    eya_interval_bounds_fields(eya_slong_t);
} eya_slong_interval_bounds_t;

/**
 * @struct eya_sllong_interval_bounds
 * @brief Interval bounds structure for signed long long integer (typically 64 bits).
 *
 * Defines a structure with `lower`
 * and `upper` fields of type `eya_sllong_t`.
 */
typedef struct eya_sllong_interval_bounds
{
    eya_interval_bounds_fields(eya_sllong_t);
} eya_sllong_interval_bounds_t;

#endif // EYA_NUMERIC_INTERVAL_BOUNDS_TYPES_H