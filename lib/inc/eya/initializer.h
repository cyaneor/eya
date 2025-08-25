/**
 * @file initializer.h
 * @brief Header file containing macros for initializing objects and structures.
 *
 * This file provides macros for simplifying the initialization of objects and structures
 * using variable arguments. The macros help reduce code duplication and provide a cleaner
 * syntax for initialization.
 */

#ifndef EYA_INITIALIZER_H
#define EYA_INITIALIZER_H

/**
 * @def eya_initializer(...)
 * @brief Initializes an object or structure with variable arguments.
 * @details This macro creates an initialization block using the provided arguments.
 *          It's particularly useful for initializing objects with multiple parameters
 *          or when the initialization syntax would otherwise be verbose.
 * @param ... Variable arguments used for initialization
 * @return A compound literal containing the initialization values
 * @note The number and types of arguments must match what the initialized object expects.
 * @warning Incorrect usage may lead to compilation errors or undefined behavior.
 *
 * Example usage:
 * @code
 * // Initialize a struct with three values
 * eya_initializer(1, 2.0f, "three");
 * @endcode
 */
#define eya_initializer(...)                                                                       \
    {                                                                                              \
        __VA_ARGS__                                                                                \
    }

/**
 * @def eya_custom_initializer(T, initializer, ...)
 * @brief Custom initializer macro that applies a specific initializer function to the arguments.
 * @details This macro provides a flexible way to initialize objects by allowing specification of
 *          both the target type and the initialization method. It's particularly useful when you
 *          need to apply custom initialization logic to a set of arguments before casting to the
 *          target type.
 *
 * @param T The target type for the initialization
 * @param initializer The initialization function/macro to apply to the arguments
 * @param ... Variable arguments passed to the initializer function
 * @return The result of applying the initializer to the arguments, cast to type T
 *
 * @note The initializer must be compatible with the provided arguments.
 * @warning Incorrect type casting or initializer usage may lead to undefined behavior.
 *
 * Example usage:
 * @code
 * // Using a custom initializer macro
 * #define MY_INIT(...) { __VA_ARGS__ }
 * int_array = eya_custom_initializer(int*, MY_INIT, 1, 2, 3, 4);
 * @endcode
 */
#define eya_custom_initializer(T, initializer, ...) ((T)initializer(__VA_ARGS__))

/**
 * @def eya_type_initializer(T, ...)
 * @brief Type-safe initializer macro that casts the initialization to type T.
 * @param T The target type for the initialization
 * @param ... Variable arguments used for initialization
 * @return A compound literal of type T containing the initialization values
 * @note This is an internal macro typically used by eya_struct_initializer
 *
 * Example usage:
 * @code
 * // Initialize and cast to MyStruct type
 * eya_type_initializer(MyStruct, 1, 2.0f);
 * @endcode
 */
#define eya_type_initializer(T, ...) eya_custom_initializer(T, eya_initializer, __VA_ARGS__)

/**
 * @def eya_struct_initializer(T, ...)
 * @brief Initializes a structure of type T with variable arguments.
 * @param T The structure type to initialize
 * @param ... Variable arguments used to initialize the structure
 * @return An initialized instance of struct T
 * @note The arguments must match the structure's fields in order and type.
 *
 * Example usage:
 * @code
 * struct Point {
 *     int x;
 *     int y;
 * };
 *
 * struct Point p = eya_struct_initializer(Point, 10, 20);
 * @endcode
 */
#define eya_struct_initializer(T, ...) eya_type_initializer(struct T, __VA_ARGS__)

#endif // EYA_INITIALIZER_H