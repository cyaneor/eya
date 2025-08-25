/**
 * @file stringify.h
 * @brief Header file containing stringification macros for C preprocessor.
 *
 * This file provides macros for converting tokens and expressions into string literals
 * at preprocessing stage. Useful for debugging, logging and metaprogramming.
 */

#ifndef EYA_STRINGIFY_H
#define EYA_STRINGIFY_H

/**
 * @def eya_stringify_token
 * @brief Converts a character or identifier
 *        to string literal using preprocessor stringification.
 *
 * This macro utilizes the # preprocessor operator to create a string representation
 * of its argument. Particularly useful for debugging and logging purposes.
 *
 * @param c Character or identifier to stringify
 * @return String literal containing the textual representation of c
 *
 * Usage examples:
 * @code
 * printf("%s\n", eya_stringify_token(ABC)); // Output: "ABC"
 * printf("%s\n", eya_stringify_token(x));   // Output: "x"
 * @endcode
 *
 * @note Works at preprocessing stage - operates on tokens rather than values
 * @warning Stringifies macro arguments verbatim without expansion
 */
#define eya_stringify_token(c) #c

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

#endif // EYA_STRINGIFY_H