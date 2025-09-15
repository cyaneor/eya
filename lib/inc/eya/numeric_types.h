/**
 * @file numeric_types.h
 * @brief Header file defining custom numeric types with the eya_ prefix.
 *
 * This file provides a set of type aliases for standard C integer types,
 * categorized into unsigned (eya_u*) and signed (eya_s*) variants with explicit prefixes.
 */

#ifndef EYA_NUMERIC_TYPES_H
#define EYA_NUMERIC_TYPES_H

/**
 * @typedef eya_uchar_t
 * @brief Alias for unsigned char (8 bits)
 */
typedef unsigned char eya_uchar_t;

/**
 * @typedef eya_ushort_t
 * @brief Alias for unsigned short integer (typically 16 bits)
 */
typedef unsigned short eya_ushort_t;

/**
 * @typedef eya_uint_t
 * @brief Alias for unsigned integer (typically 32 bits)
 */
typedef unsigned int eya_uint_t;

/**
 * @typedef eya_ulong_t
 * @brief Alias for unsigned long integer
 *        (typically 32 or 64 bits depending on platform)
 */
typedef unsigned long eya_ulong_t;

/**
 * @typedef eya_ullong_t
 * @brief Alias for unsigned long long integer (typically 64 bits)
 */
typedef unsigned long long eya_ullong_t;

/**
 * @typedef eya_schar_t
 * @brief Alias for signed char (8 bits)
 */
typedef char eya_schar_t;

/**
 * @typedef eya_sshort_t
 * @brief Alias for signed short integer (typically 16 bits)
 */
typedef short eya_sshort_t;

/**
 * @typedef eya_sint_t
 * @brief Alias for signed integer (typically 32 bits)
 */
typedef int eya_sint_t;

/**
 * @typedef eya_slong_t
 * @brief Alias for signed long integer
 *        (typically 32 or 64 bits depending on platform)
 */
typedef long eya_slong_t;

/**
 * @typedef eya_sllong_t
 * @brief Alias for signed long long integer (typically 64 bits)
 */
typedef long long eya_sllong_t;

#endif /* EYA_NUMERIC_TYPES_H */