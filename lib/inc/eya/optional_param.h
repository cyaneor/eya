/**
 * @file optional_param.h
 * @brief Header file containing a macro
 *        for handling optional parameters.
 *
 * This file defines the `eya_optional_param` macro,
 * which allows easy creation of optional parameters
 * with default values in functions.
 */

#ifndef EYA_OPTIONAL_PARAM_H
#define EYA_OPTIONAL_PARAM_H

#include "nullptr.h"

/**
 * @brief Macro for creating an optional parameter
 *        with a specified default value.
 *
 * This macro initializes a local variable with the given default value
 * and sets the pointer to this variable if the passed parameter equals nullptr.
 *
 * @param T Parameter type.
 * @param N Parameter name.
 * @param ... Default value for the parameter.
 *
 * @note Use this macro
 *       to simplify handling of optional parameters in functions.
 *
 * Example of macro usage:
 * @code
 * void example_function(int* value) {
 *     eya_optional_param(int, value, 42);
 *     // Now value points to 42 if nullptr was passed.
 *     printf("Value: %d\n", *value);
 * }
 * @endcode
 */
#define eya_optional_param(T, N, ...)                                                              \
    T _##N = __VA_ARGS__;                                                                          \
    if (N == nullptr)                                                                              \
    N = &_##N

#endif // EYA_OPTIONAL_PARAM_H