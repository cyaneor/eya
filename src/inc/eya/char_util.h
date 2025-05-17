#ifndef EYA_CHAR_UTIL_H
#define EYA_CHAR_UTIL_H

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

#endif // EYA_CHAR_UTIL_H
