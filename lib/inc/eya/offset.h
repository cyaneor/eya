/**
 * @file offset.h
 * @brief Header file defining memory offset types.
 *
 * This file contains type definitions for signed and unsigned memory offsets:
 *
 * - @c eya_soffset_t for signed offsets
 * - @c eya_uoffset_t for unsigned offsets
 *
 * These types are used when working with memory addresses and indices,
 * such as when manipulating buffers or arrays.
 * - The @c eya_soffset_t type supports both positive and negative values,
 *   useful for offset calculations that may require bidirectional displacement.
 * - The @c eya_uoffset_t type is restricted to non-negative values and should be used
 *   for index operations where negative values are invalid.
 *
 * This file includes the @c "size.h" header to utilize the base types
 * @c eya_ssize_t and @c eya_usize_t, which serve as underlying types for
 * @c eya_soffset_t and @c eya_uoffset_t respectively.
 */

#ifndef EYA_OFFSET_H
#define EYA_OFFSET_H

#include "size.h"

/**
 * @typedef eya_soffset_t
 * @brief Type representing signed memory offsets.
 *
 * Used for storing memory offsets that may be negative,
 * such as when working with backward array/buffer addresses.
 * Alias for @c eya_ssize_t type.
 */
typedef eya_ssize_t eya_soffset_t;

/**
 * @typedef eya_uoffset_t
 * @brief Type representing unsigned memory offsets.
 *
 * Used for storing memory offsets that must be non-negative,
 * typically for forward array index operations.
 * Alias for @c eya_usize_t type.
 */
typedef eya_usize_t eya_uoffset_t;

#endif // EYA_OFFSET_H