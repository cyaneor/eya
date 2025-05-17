#ifndef EYA_STR_UTIL_H
#define EYA_STR_UTIL_H

#include "char_util.h"

/**
 * @def eya_stringify_va
 * @brief Creates a string literal from the provided arguments.
 *
 * This macro wraps `eya_stringify_token`,
 * allowing a variable number of arguments to be passed.
 * Used for convenient conversion of arguments into a string.
 *
 * @param ... Variable number of arguments to be converted into a string.
 * @return String literal representing the provided arguments.
 *
 * Example usage:
 * @code
 * printf("%s\n", eya_stringify_va(123));       // Output: "123"
 * printf("%s\n", eya_stringify_va(x + y));     // Output: "x + y"
 * @endcode
 */
#define eya_stringify_va(...) eya_stringify_token(__VA_ARGS__)

#endif // EYA_STR_UTIL_H