/**
 * @file memory_view_cast.h
 * @brief Header providing memory view pointer casting utilities
 *
 * This header defines a convenience macro for type-safe casting to memory view pointers.
 * It builds upon the core pointer utilities and memory view types to provide a clean
 * interface for working with memory regions.
 *
 * The main component is the eya_memory_view_cast macro which simplifies:
 * - Type-safe conversion to eya_memory_view_t pointers
 * - Consistent memory view handling across the codebase
 *
 * @see memory_view.h for the base memory view type definition
 * @see ptr_util.h for the underlying casting mechanism
 */

#ifndef EYA_MEMORY_VIEW_CAST_H
#define EYA_MEMORY_VIEW_CAST_H

#include "memory_view.h"
#include "ptr_util.h"

/**
 * @def eya_memory_view_cast(ptr)
 * @brief Convenience macro to cast a pointer to an eya_memory_view_t pointer.
 *
 * This macro provides a shorthand for casting any pointer to a pointer of type
 * eya_memory_view_t (memory view structure pointer). It internally uses eya_ptr_cast.
 *
 * @param ptr Pointer to cast to eya_memory_view_t*
 * @return Pointer of type eya_memory_view_t*
 *
 * @see eya_ptr_cast()
 * @see eya_memory_view_t
 *
 * Example usage:
 * @code
 * void* some_ptr = ...;
 * eya_memory_view_t* view = eya_memory_view_cast(some_ptr);
 * @endcode
 */
#define eya_memory_view_cast(ptr) eya_ptr_cast(eya_memory_view_t, ptr)

#endif // EYA_MEMORY_VIEW_CAST_H
