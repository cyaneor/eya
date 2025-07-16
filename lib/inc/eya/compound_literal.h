/**
 * @file compound_literal.h
 * @brief Compound literal utilities
 *        for creating temporary objects with automatic storage duration.
 */

#ifndef EYA_COMPOUND_LITERAL_H
#define EYA_COMPOUND_LITERAL_H

#include "initializer.h"

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
 * Vec2* v = eya_compound_literal_make(Vec2, .x=1.0f, .y=2.0f);
 * @endcode
 */
#define eya_compound_literal_make(T, ...) &eya_type_initializer(T, __VA_ARGS__)

#endif // EYA_COMPOUND_LITERAL_H