/**
 * @file elif.h
 * @brief Header file containing a macro
 *        for a simplified version of the `else if` operator.
 *
 * This file defines the `elif` macro,
 * which serves as an alternative to the standard `else if` operator in C.
 *
 * Using this macro enhances code readability and expressiveness,
 * which can be beneficial for certain corporate coding standards
 * or improving visual code perception.
 *
 * @note This macro is intended to simplify conditional statements,
 *       but caution is needed when using it to avoid reducing code clarity
 *       for other developers.
 */

#ifndef EYA_ELIF_H
#define EYA_ELIF_H

/**
 * @def elif
 * @brief Simplified version of the `else if` operator.
 *
 * This macro provides an alternative syntax for the `else if` construct,
 * improving code readability or complying with corporate coding standards.
 *
 * @note Use this macro to make code more expressive and concise.
 *
 * Usage example:
 * @code
 * if (condition1) {
 *     // Actions when condition1 is met
 * }
 * elif (condition2) {
 *     // Actions when condition2 is met
 * }
 * else {
 *     // Default actions
 * }
 * @endcode
 */
#ifndef elif
#    define elif else if
#endif // elif

#endif // EYA_ELIF_H