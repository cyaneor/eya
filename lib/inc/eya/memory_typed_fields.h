/**
 * @file memory_typed_fields.h
 * @brief Header for typed memory range field definitions with size information
 *
 * Provides macros for declaring structure fields that represent typed memory ranges
 * with built-in type size information. This builds upon the basic memory range
 * functionality while adding type safety features.
 *
 * Key Features:
 * - Type-aware memory range representation
 * - Self-describing structures with built-in element size
 * - Compatible with range-based operations
 * - Interoperable with raw memory operations
 *
 * The primary macro @ref eya_memory_typed_fields(T) generates:
 * - Standard begin/end pointers (from @ref eya_memory_range_fields)
 * - Additional element_size field storing sizeof(T)
 *
 * Typical usage patterns:
 * - Memory buffers with runtime type checking
 * - Serialization/deserialization systems
 * - Generic memory manipulation utilities
 *
 * @see eya_memory_range_fields.h
 * @see size.h for eya_usize_t definition
 */

#ifndef EYA_MEMORY_TYPED_FIELDS_H
#define EYA_MEMORY_TYPED_FIELDS_H

#include "memory_range_fields.h"
#include "size.h"

/**
 * @def eya_memory_typed_fields(T)
 * @brief Defines standard fields for a typed memory range structure with size information.
 *
 * This macro expands to declare:
 * 1. Standard memory range fields (begin and end pointers)
 * 2. An additional field storing the size of the element type
 *
 * @tparam T The type of elements in the memory range
 *
 * The macro generates the following fields:
 * @code
 * {
 *     T *begin;               // Pointer to the start of the memory region
 *     T *end;                 // Pointer to the end of the memory region (exclusive)
 *     eya_usize_t element_size;  // Size of individual elements in bytes
 * }
 * @endcode
 *
 * @note The memory region follows [begin, end) semantics (inclusive begin, exclusive end)
 * @note The element_size field is automatically set to sizeof(T) when initialized properly
 *
 * @see eya_memory_range_fields()
 *
 * Example usage:
 * @code
 * struct TypedBuffer {
 *     eya_memory_typed_fields(float);  // Creates begin/end pointers and element_size
 * };
 *
 * // Initialization would typically set:
 * // buffer.element_size = sizeof(float);
 * @endcode
 */
#define eya_memory_typed_fields(T)                                                                 \
    eya_memory_range_fields(T);                                                                    \
    eya_usize_t element_size

#endif // EYA_MEMORY_TYPED_FIELDS_H
