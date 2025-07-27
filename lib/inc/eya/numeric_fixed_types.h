/**
 * @file numeric_fixed_types.h
 * @brief Fixed-size integer type definitions for cross-platform compatibility.
 *
 * This header defines a set of fixed-size signed and unsigned integer types
 * (8, 16, 32, and 64-bit) to ensure consistent data representation across
 * different architectures and compilers. The types are implemented as aliases
 * for the base numeric types defined in "numeric_types.h".
 *
 * @details Provides type-safe typedefs that explicitly specify bit-widths,
 *          enabling:
 *
 *          - Predictable memory layout for data structures
 *          - Binary compatibility across platforms
 *          - Explicit control over integer ranges
 *
 * Unsigned types range from eya_u8_t (8-bit) to eya_u64_t (64-bit).
 * Signed types range from eya_s8_t (8-bit) to eya_s64_t (64-bit).
 *
 * @note These types should be preferred over native C types
 *       when serialization or cross-platform consistency is required.
 */

#ifndef EYA_NUMERIC_FIXED_TYPES_H
#define EYA_NUMERIC_FIXED_TYPES_H

#include "numeric_types.h"

/**
 * @typedef eya_u8_t
 * @brief Fixed-size unsigned 8-bit integer type.
 * @details This type ensures a fixed size of 8 bits for unsigned integers.
 */
typedef eya_uchar_t eya_u8_t;

/**
 * @typedef eya_u16_t
 * @brief Fixed-size unsigned 16-bit integer type.
 * @details This type ensures a fixed size of 16 bits for unsigned integers.
 */
typedef eya_ushort_t eya_u16_t;

/**
 * @typedef eya_u32_t
 * @brief Fixed-size unsigned 32-bit integer type.
 * @details his type ensures a fixed size of 32 bits for unsigned integers.
 */
typedef eya_uint_t eya_u32_t;

/**
 * @typedef eya_u64_t
 * @brief Fixed-size unsigned 64-bit integer type.
 * @details This type ensures a fixed size of 64 bits for unsigned integers.
 */
typedef eya_ullong_t eya_u64_t;

/**
 * @typedef eya_s8_t
 * @brief Fixed-size signed 8-bit integer type.
 * @details This type ensures a fixed size of 8 bits for signed integers.
 */
typedef eya_schar_t eya_s8_t;

/**
 * @typedef eya_s16_t
 * @brief Fixed-size signed 16-bit integer type.
 * @details This type ensures a fixed size of 16 bits for signed integers.
 */
typedef eya_sshort_t eya_s16_t;

/**
 * @typedef eya_s32_t
 * @brief Fixed-size signed 32-bit integer type.
 * @details This type ensures a fixed size of 32 bits for signed integers.
 */
typedef eya_sint_t eya_s32_t;

/**
 * @typedef eya_s64_t
 * @brief Fixed-size signed 64-bit integer type.
 * @details This type ensures a fixed size of 64 bits for signed integers.
 */
typedef eya_sllong_t eya_s64_t;

#endif // EYA_NUMERIC_FIXED_TYPES_H