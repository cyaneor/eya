/**
 * @file static_string_size.h
 * @brief Header for static string length calculation macro
 *
 * Defines the `eya_static_string_size` macro to compute the length of
 * null-terminated static strings excluding the terminating null character.
 */

#ifndef EYA_STATIC_STRING_SIZE_H
#define EYA_STATIC_STRING_SIZE_H

#include "static_array_size.h"

/**
 * @def eya_static_string_size
 * @brief Calculates static string length (excluding null terminator)
 *
 * Computes the length of statically allocated character arrays by
 * using `eya_static_array_size` and subtracting 1 to exclude the
 * terminating null character (`\0`).
 *
 * @param x Static character array (string) to measure
 * @return Length of string excluding null terminator
 *
 * @note Only valid for proper character arrays - unsafe for:
 *       - Pointers to strings
 *       - Non-char array types
 *       - Arrays without null terminators
 *
 * @see eya_static_array_size
 *
 * Usage example:
 * @code
 * char str[] = "Hello";
 * constexpr auto len = eya_static_string_size(str); // len == 5
 * @endcode
 */
#define eya_static_string_size(x) (eya_static_array_size(x) - 1)

#endif // EYA_STATIC_STRING_SIZE_H