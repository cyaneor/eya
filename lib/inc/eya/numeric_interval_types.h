/**
 * @file numeric_interval_types.h
 * @brief Defines interval types for various numeric data types.
 *
 * This header provides type definitions for interval structures corresponding
 * to different numeric types (unsigned and signed integers of various sizes).
 *
 * Each interval type uses the `eya_interval_fields` macro to define its fields,
 * which include bounds (lower and upper) and flags indicating the interval's openness.
 */

#ifndef EYA_NUMERIC_INTERVAL_TYPES_H
#define EYA_NUMERIC_INTERVAL_TYPES_H

#include <eya/interval_fields.h>
#include <eya/numeric_interval_bounds_types.h>

/**
 * @struct eya_uchar_interval
 * @brief Interval structure for unsigned char type.
 *
 * Contains the bounds (lower and upper) of type `eya_uchar_interval_bounds_t`
 * and flags of type `eya_interval_flags_t` to specify boundary conditions.
 */
typedef struct eya_uchar_interval
{
    eya_interval_fields(eya_uchar_interval_bounds_t);
} eya_uchar_interval_t;

/**
 * @struct eya_ushort_interval
 * @brief Interval structure for unsigned short type.
 *
 * Contains the bounds (lower and upper) of type `eya_ushort_interval_bounds_t`
 * and flags of type `eya_interval_flags_t` to specify boundary conditions.
 */
typedef struct eya_ushort_interval
{
    eya_interval_fields(eya_ushort_interval_bounds_t);
} eya_ushort_interval_t;

/**
 * @struct eya_uint_interval
 * @brief Interval structure for unsigned int type.
 *
 * Contains the bounds (lower and upper) of type `eya_uint_interval_bounds_t`
 * and flags of type `eya_interval_flags_t` to specify boundary conditions.
 */
typedef struct eya_uint_interval
{
    eya_interval_fields(eya_uint_interval_bounds_t);
} eya_uint_interval_t;

/**
 * @struct eya_ulong_interval
 * @brief Interval structure for unsigned long type.
 *
 * Contains the bounds (lower and upper) of type `eya_ulong_interval_bounds_t`
 * and flags of type `eya_interval_flags_t` to specify boundary conditions.
 */
typedef struct eya_ulong_interval
{
    eya_interval_fields(eya_ulong_interval_bounds_t);
} eya_ulong_interval_t;

/**
 * @struct eya_ullong_interval
 * @brief Interval structure for unsigned long long type.
 *
 * Contains the bounds (lower and upper) of type `eya_ullong_interval_bounds_t`
 * and flags of type `eya_interval_flags_t` to specify boundary conditions.
 */
typedef struct eya_ullong_interval
{
    eya_interval_fields(eya_ullong_interval_bounds_t);
} eya_ullong_interval_t;

/**
 * @struct eya_schar_interval
 * @brief Interval structure for signed char type.
 *
 * Contains the bounds (lower and upper) of type `eya_schar_interval_bounds_t`
 * and flags of type `eya_interval_flags_t` to specify boundary conditions.
 */
typedef struct eya_schar_interval
{
    eya_interval_fields(eya_schar_interval_bounds_t);
} eya_schar_interval_t;

/**
 * @struct eya_sshort_interval
 * @brief Interval structure for short type.
 *
 * Contains the bounds (lower and upper) of type `eya_sshort_interval_bounds_t`
 * and flags of type `eya_interval_flags_t` to specify boundary conditions.
 */
typedef struct eya_sshort_interval
{
    eya_interval_fields(eya_sshort_interval_bounds_t);
} eya_sshort_interval_t;

/**
 * @struct eya_sint_interval
 * @brief Interval structure for int type.
 *
 * Contains the bounds (lower and upper) of type `eya_sint_interval_bounds_t`
 * and flags of type `eya_interval_flags_t` to specify boundary conditions.
 */
typedef struct eya_sint_interval
{
    eya_interval_fields(eya_sint_interval_bounds_t);
} eya_sint_interval_t;

/**
 * @struct eya_slong_interval
 * @brief Interval structure for long type.
 *
 * Contains the bounds (lower and upper) of type `eya_slong_interval_bounds_t`
 * and flags of type `eya_interval_flags_t` to specify boundary conditions.
 */
typedef struct eya_slong_interval
{
    eya_interval_fields(eya_slong_interval_bounds_t);
} eya_slong_interval_t;

/**
 * @struct eya_sllong_interval
 * @brief Interval structure for long long type.
 *
 * Contains the bounds (lower and upper) of type `eya_sllong_interval_bounds_t`
 * and flags of type `eya_interval_flags_t` to specify boundary conditions.
 */
typedef struct eya_sllong_interval
{
    eya_interval_fields(eya_sllong_interval_bounds_t);
} eya_sllong_interval_t;

#endif // EYA_NUMERIC_INTERVAL_TYPES_H