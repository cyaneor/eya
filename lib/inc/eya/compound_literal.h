/**
 * @file compound_literal.h
 * @brief Macros for creating compound literals with custom initialization
 *
 * This header provides macros for creating pointers
 * to temporary initialized objects (compound literals)
 * with either direct initialization or custom initializer functions.
 *
 * The created objects have automatic storage duration
 * and their lifetime is limited to the enclosing scope.
 *
 * The macros provide a convenient way to:
 * - Create temporary initialized objects on the stack
 * - Get pointers to these objects for immediate use
 * - Support both direct initialization and custom initializer functions
 *
 * @warning The returned pointers must not be stored
 *          as they become invalid when the object goes out of scope.
 *
 * Example usage:
 * @code
 * // With direct initialization
 * struct Point { int x, y; };
 * Point* p = eya_compound_literal(Point, .x=10, .y=20);
 *
 * // With custom initializer
 * Point point_init(int x, int y) { return (Point){x, y}; }
 * Point* p2 = eya_compound_literal_of(Point, point_init, 30, 40);
 * @endcode
 *
 * @see initializer.h for the underlying initialization mechanism
 */

#ifndef EYA_COMPOUND_LITERAL_H
#define EYA_COMPOUND_LITERAL_H

#include "initializer.h"

/**
 * @def eya_compound_literal_of
 * @brief Creates a pointer to a compound literal using a custom initializer function.
 *
 * This macro constructs an anonymous instance of type `T` initialized by calling
 * the specified custom initializer function with the provided arguments, then returns its address.
 * The object has automatic storage duration (typically stack-allocated).
 *
 * @note The lifetime of the returned pointer is limited to the enclosing scope.
 *       Do not store it for later use.
 *
 * @param T Type of the object to create (must be a complete type).
 * @param initializer Custom initializer function to use for object initialization.
 * @param ... Arguments to pass to the custom initializer function.
 * @return Pointer to a newly initialized temporary object of type `T`.
 *
 * Usage example:
 * @code
 * struct Vec2 { float x, y; };
 * Vec2 vec2_init(float x, float y) { return (Vec2){x, y}; }
 * Vec2* v = eya_compound_literal_of(Vec2, vec2_init, 1.0f, 2.0f);
 * @endcode
 *
 * @see eya_compound_literal
 */
#define eya_compound_literal_of(T, initializer, ...)                                              \
    &eya_custom_initializer(T, initializer, __VA_ARGS__)

/**
 * @brief Creates a pointer to a compound literal (temporary initialized object).
 *
 * This macro constructs an anonymous instance of type `T`
 * initialized with the given arguments, then returns its address.
 * The object has automatic storage duration (typically stack-allocated).
 *
 * @note The lifetime of the returned pointer is limited to the enclosing scope.
 *       Do not store it for later use.
 *
 * @param T Type of the object to create (must be a complete type).
 * @param ... Initializer arguments compatible with `T`'s structure.
 * @return Pointer to a newly initialized temporary object of type `T`.
 *
 * Usage example:
 * @code
 * struct Vec2 { float x, y; };
 * Vec2* v = eya_compound_literal(Vec2, .x=1.0f, .y=2.0f);
 * @endcode
 */
#define eya_compound_literal(T, ...) &eya_type_initializer(T, __VA_ARGS__)

#endif // EYA_COMPOUND_LITERAL_H