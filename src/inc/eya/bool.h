/**
 * @file bool.h
 * @brief Header providing boolean type emulation for C language.
 *
 * This header defines the boolean type `bool` with values `true` and `false`
 * for use in C environments lacking native bool support (pre-C99 standard).
 *
 * The implementation checks for existing boolean definitions (from C++ or C99's stdbool.h)
 * and only provides the custom type when native support is unavailable.
 *
 * @note No definitions are made when compiling as C++ or when stdbool.h is detected.
 */

#ifndef SE_BOOL_H
#define SE_BOOL_H

#if !defined(__cplusplus) && !defined(__STDBOOL_H)
/**
 * @enum bool
 * @brief Enumeration type representing boolean values.
 *
 * The `bool` enum provides logical truth values for C code,
 * offering a standardized way to handle boolean logic in
 * environments without built-in boolean support.
 *
 * Enum values:
 * - `false`: Logical false value
 * - `true`: Logical true value
 *
 * Usage example:
 * @code
 * #include <se/bool.h>
 *
 * bool is_valid = true;
 * if (is_valid) {
 *     // Actions for true condition
 * }
 * @endcode
 */
typedef enum
{
    false, /**< Boolean `false` value representation */
    true   /**< Boolean `true` value representation */
} bool;

#endif // !defined(__cplusplus) && !defined(__STDBOOL_H)

#endif // SE_BOOL_H