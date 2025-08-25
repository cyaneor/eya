/**
 * @file ptr_util.h
 * @brief Utility macros for pointer operations and manipulations.
 *
 * This header provides a comprehensive set of macros for safe and unsafe pointer operations,
 * including casting, dereferencing, arithmetic, alignment, and range checking.
 *
 * The macros are designed to:
 * - Provide type-safe pointer operations
 * - Support both safe (with null checks) and unsafe variants
 * - Enable address arithmetic and manipulation
 * - Facilitate memory alignment operations
 * - Check for pointer ranges and overlaps
 *
 * @note Many operations come in both safe and unsafe variants:
 *       - Unsafe variants (suffixed with _unsafe) assume valid inputs
 *       - Safe variants perform basic null checks
 *
 * @warning Even "safe" variants don't guarantee memory safety - they only add null checks.
 *          Proper memory bounds and validity must still be ensured by the caller.
 *
 * Key functionality groups:
 * - Basic pointer operations: casting, dereferencing, null checks
 * - Pointer arithmetic: addition/subtraction with offsets
 * - Address conversion: to unsigned/signed numeric addresses
 * - Alignment operations: align up/down to boundaries
 * - Range checking: overlap detection between pointer ranges
 *
 * @see addr_util.h For underlying address manipulation utilities
 * @see nullptr.h For nullptr definition
 *
 * Example usage:
 * @code
 * void* data = ...;
 *
 * // Safe pointer arithmetic
 * void* next = eya_ptr_add_by_offset(data, sizeof(int));
 *
 * // Type-safe dereference
 * int value = eya_ptr_deref(int, data);
 *
 * // Alignment operations
 * void* aligned = eya_ptr_align_up(data, 16);
 * @endcode
 */

#ifndef EYA_PTR_UTIL_H
#define EYA_PTR_UTIL_H

#include "addr_util.h"
#include "nullptr.h"

/**
 * @def eya_ptr_cast(T, ptr)
 * @brief Casts a pointer to a pointer of type T.
 *
 * @param T Target type (without pointer).
 * @param ptr Pointer to cast.
 * @return Pointer of type T*.
 */
#define eya_ptr_cast(T, ptr) eya_type_cast(T *, ptr)

/**
 * @def eya_cptr_cast(T, ptr)
 * @brief Casts a pointer to a const pointer of type T.
 *
 * @param T Target type (without const or pointer).
 * @param ptr Pointer to cast.
 * @return Const pointer of type const T*.
 */
#define eya_cptr_cast(T, ptr) eya_ptr_cast(const T, ptr)

/**
 * @def eya_ptr_deref(T, ptr)
 * @brief Dereferences a pointer cast to type T*.
 *
 * Safely casts the pointer to a pointer of type T and dereferences it,
 * resulting in an lvalue of type T.
 *
 * @param T   Target type (without pointer).
 * @param ptr Pointer to cast and dereference.
 * @return    Lvalue reference of type T.
 *
 * @note This is essentially a type-safe combination of pointer cast and dereference.
 * @warning The caller must ensure the pointer is valid and properly aligned.
 *
 * Example usage:
 * @code
 * void* data = ...;
 * int value = eya_ptr_deref(int, data);  // Equivalent to: *(int*)data
 * @endcode
 *
 * @see eya_ptr_cast()
 */
#define eya_ptr_deref(T, ptr) (*eya_ptr_cast(T, ptr))

/**
 * @def eya_ptr_is_null(ptr)
 * @brief Checks if a pointer is null.
 * @param ptr Pointer to check.
 * @return true if pointer is nullptr, false otherwise.
 */
#define eya_ptr_is_null(ptr) ((ptr) == nullptr)

/**
 * @def eya_ptr_to_const_char
 * @brief Converts a pointer to a const char pointer.
 *
 * This macro performs a type cast to convert any pointer type
 * to a const char pointer type.
 *
 * @param ptr Pointer to convert.
 * @return Converted pointer of type const char*.
 */
#define eya_ptr_to_const_char(ptr) eya_ptr_cast(const char, ptr)

/**
 * @def eya_ptr_to_uaddr
 * @brief Converts any pointer to an unsigned address type (eya_uaddr_t).
 *
 * This macro first converts the pointer to const char* using eya_ptr_to_const_char,
 * then performs a reinterpret cast to eya_uaddr_t.
 *
 * @param ptr Pointer to convert.
 * @return Converted value of type eya_uaddr_t.
 */
#define eya_ptr_to_uaddr(ptr) eya_reinterpret_cast(eya_uaddr_t, eya_ptr_to_const_char(ptr))

/**
 * @def eya_ptr_to_saddr
 * @brief Converts any pointer to a signed address type (eya_saddr_t).
 *
 * This macro first converts the pointer to const char* using eya_ptr_to_const_char,
 * then performs a reinterpret cast to eya_saddr_t.
 *
 * @param ptr Pointer to convert.
 * @return Converted value of type eya_saddr_t.
 */
#define eya_ptr_to_saddr(ptr) eya_reinterpret_cast(eya_saddr_t, eya_ptr_to_const_char(ptr))

/**
 * @def eya_ptr_sdiff
 * @brief Calculates the signed difference between two pointers.
 * @param ptr1 First pointer.
 * @param ptr2 Second pointer.
 * @return Signed difference between pointers as eya_saddr_t.
 */
#define eya_ptr_sdiff(ptr1, ptr2) eya_addr_diff(eya_ptr_to_saddr(ptr1), eya_ptr_to_saddr(ptr2))

/**
 * @def eya_ptr_udiff
 * @brief Calculates the unsigned difference between two pointers.
 * @param ptr1 First pointer.
 * @param ptr2 Second pointer.
 * @return Unsigned difference between pointers as eya_uaddr_t.
 */
#define eya_ptr_udiff(ptr1, ptr2) eya_addr_diff(eya_ptr_to_uaddr(ptr1), eya_ptr_to_uaddr(ptr2))

/**
 * @def eya_ptr_is_aligned(ptr, align)
 * @brief Checks if a pointer is aligned to the specified boundary.
 * @param ptr Pointer to check.
 * @param align Alignment boundary to check against.
 * @return true if the pointer is aligned, false otherwise.
 */
#define eya_ptr_is_aligned(ptr, align) eya_addr_is_aligned(eya_ptr_to_uaddr(ptr), align)

/**
 * @def eya_ptr_ranges_no_overlap(r1_begin, r2_begin, r2_end)
 * @brief Checks if two pointer ranges do not overlap.
 * @param r1_begin Beginning of first range.
 * @param r2_begin Beginning of second range.
 * @param r2_end End of second range.
 * @return true if ranges do not overlap, false otherwise.
 */
#define eya_ptr_ranges_no_overlap(r1_begin, r2_begin, r2_end)                                      \
    (((r1_begin) <= (r2_begin)) || ((r2_end) <= (r1_begin)))

/**
 * @def eya_ptr_ranges_is_overlap(r1_begin, r2_begin, r2_end)
 * @brief Checks if two pointer ranges overlap.
 * @param r1_begin Beginning of first range.
 * @param r2_begin Beginning of second range.
 * @param r2_end End of second range.
 * @return true if ranges overlap, false otherwise.
 */
#define eya_ptr_ranges_is_overlap(r1_begin, r2_begin, r2_end)                                      \
    (!eya_ptr_ranges_no_overlap(r1_begin, r2_begin, r2_end))

/**
 * @def eya_ptr_add_by_offset_unsafe(ptr, offset)
 * @brief Adds an offset to a pointer without safety checks (unsafe operation)
 * @details Performs pointer arithmetic by:
 *          1. Converting the pointer to an unsigned address (eya_uaddr_t)
 *          2. Adding the specified offset
 *          3. Converting back to a void pointer
 *
 * @warning This is an unsafe operation that does not validate:
 *          - Pointer validity
 *          - Offset bounds
 *          - Resulting address alignment
 *          - Potential overflow conditions
 *
 * @param ptr Base pointer to offset from
 * @param offset Unsigned offset to add (in bytes)
 * @return void* pointer at the calculated address
 */
#define eya_ptr_add_by_offset_unsafe(ptr, offset)                                                  \
    eya_addr_to_void(eya_math_add(eya_ptr_to_uaddr(ptr), offset))

/**
 * @def eya_ptr_sub_by_offset_unsafe(ptr, offset)
 * @brief Subtracts an offset from a pointer without safety checks (unsafe operation)
 * @details Performs pointer arithmetic by:
 *          1. Converting the pointer to an unsigned address (eya_uaddr_t)
 *          2. Subtracting the specified offset
 *          3. Converting back to a void pointer
 *
 * @warning This is an unsafe operation that does not validate:
 *          - Pointer validity
 *          - Offset bounds (must not be greater than original address)
 *          - Resulting address alignment
 *          - Potential underflow conditions
 *          - Whether the resulting pointer is within valid memory bounds
 *
 * @param ptr Base pointer to offset from (must be non-null)
 * @param offset Unsigned offset to subtract (in bytes, must be ≤ original address)
 * @return void* pointer at the calculated address
 */
#define eya_ptr_sub_by_offset_unsafe(ptr, offset)                                                  \
    eya_addr_to_void(eya_math_sub(eya_ptr_to_uaddr(ptr), offset))

/**
 * @def eya_ptr_add_by_offset(ptr, offset)
 * @brief Safely adds an offset to a pointer with null-checking
 * @details Performs pointer arithmetic with safety checks:
 *          1. First validates pointer is not null (returns null if input is null)
 *          2. Otherwise performs addition via eya_ptr_add_by_offset_unsafe()
 *
 *          Provides basic protection against:
 *          - Null pointer dereferencing
 *          - Some invalid memory access cases
 *
 * @warning Still requires caution about:
 *          - Offset magnitude (potential overflow)
 *          - Resulting address validity
 *          - Memory region boundaries
 *          - Alignment requirements
 *
 * @param ptr Base pointer to offset from (may be null)
 * @param offset Unsigned offset to add (in bytes)
 * @return void* pointer at the calculated address, or null if input was null
 *
 * @see eya_ptr_add_by_offset_unsafe() For the unsafe version without null checks
 * @see eya_ptr_is_null() Used for the null check
 * @note Safer than unsafe version but still doesn't validate memory bounds
 */
#define eya_ptr_add_by_offset(ptr, offset)                                                         \
    (eya_ptr_is_null(ptr) ? ptr : eya_ptr_add_by_offset_unsafe(ptr, offset))

/**
 * @def eya_ptr_sub_by_offset(ptr, offset)
 * @brief Safely subtracts an offset from a pointer with null-checking
 * @details Performs pointer subtraction with safety checks:
 *          1. First checks if pointer is null (returns null if true)
 *          2. Otherwise performs subtraction via eya_ptr_sub_by_offset_unsafe()
 *
 *          This provides basic protection against:
 *          - Null pointer dereferencing
 *          - Some invalid memory access cases
 *
 * @warning Still requires caution about:
 *          - Offset bounds (must not be greater than original address)
 *          - Resulting address validity
 *          - Potential underflow conditions
 *          - Memory region boundaries
 *
 * @param ptr Base pointer to offset from (may be null)
 * @param offset Unsigned offset to subtract (in bytes, must be ≤ original address)
 * @return void* pointer at the calculated address, or null if input was null
 *
 * @see eya_ptr_sub_by_offset_unsafe() For the unsafe version without null checks
 * @see eya_ptr_is_null() Used for the null check
 */
#define eya_ptr_sub_by_offset(ptr, offset)                                                         \
    (eya_ptr_is_null(ptr) ? ptr : eya_ptr_sub_by_offset_unsafe(ptr, offset))

/**
 * @def eya_ptr_add_unsafe(ptr1, ptr2)
 * @brief Performs unsafe pointer addition (no bounds checking)
 * @details Adds two pointers by:
 *          1. Converting ptr2 to numeric address
 *          2. Adding to ptr1 as an offset
 *
 * @warning This is an unsafe operation that:
 *          - Performs no null checking
 *          - Doesn't validate resulting address
 *          - May cause overflow
 *          - Doesn't check alignment
 *
 * @param ptr1 Base pointer
 * @param ptr2 Pointer to convert to offset
 * @return void* result of addition
 * @see eya_ptr_add_by_offset_unsafe()
 */
#define eya_ptr_add_unsafe(ptr1, ptr2) eya_ptr_add_by_offset_unsafe(ptr1, eya_ptr_to_uaddr(ptr2))

/**
 * @def eya_ptr_sub_unsafe(ptr1, ptr2)
 * @brief Performs unsafe pointer subtraction (no bounds checking)
 * @details Subtracts pointers by:
 *          1. Converting ptr2 to numeric address
 *          2. Subtracting from ptr1 as offset
 *
 * @warning This is an unsafe operation that:
 *          - Performs no null checking
 *          - May cause underflow
 *          - Doesn't validate resulting address
 *
 * @param ptr1 Base pointer
 * @param ptr2 Pointer to convert to offset
 * @return void* result of subtraction
 * @see eya_ptr_sub_by_offset_unsafe()
 */
#define eya_ptr_sub_unsafe(ptr1, ptr2) eya_ptr_sub_by_offset_unsafe(ptr1, eya_ptr_to_uaddr(ptr2))

/**
 * @def eya_ptr_add(ptr1, ptr2)
 * @brief Safer pointer addition with null checking
 * @details Adds pointers with null check:
 *          1. Returns null if ptr1 is null
 *          2. Otherwise converts ptr2 to offset and adds
 *
 *          Still requires caution about:
 *          - Resulting address validity
 *          - Potential overflow
 *
 * @param ptr1 Base pointer (may be null)
 * @param ptr2 Pointer to convert to offset
 * @return void* result or null if ptr1 was null
 * @see eya_ptr_add_by_offset()
 */
#define eya_ptr_add(ptr1, ptr2) eya_ptr_add_by_offset(ptr1, eya_ptr_to_uaddr(ptr2))

/**
 * @def eya_ptr_sub(ptr1, ptr2)
 * @brief Safer pointer subtraction with null checking
 * @details Subtracts pointers with null check:
 *          1. Returns null if ptr1 is null
 *          2. Otherwise converts ptr2 to offset and subtracts
 *
 *          Still requires caution about:
 *          - Resulting address validity
 *          - Potential underflow
 *
 * @param ptr1 Base pointer (may be null)
 * @param ptr2 Pointer to convert to offset
 * @return void* result or null if ptr1 was null
 * @see eya_ptr_sub_by_offset()
 */
#define eya_ptr_sub(ptr1, ptr2) eya_ptr_sub_by_offset(ptr1, eya_ptr_to_uaddr(ptr2))

/**
 * @def eya_ptr_align_up(ptr, align)
 * @brief Aligns a pointer up to the next specified boundary
 * @details Adjusts the pointer to the nearest higher (or equal) memory address
 *          that matches the specified alignment boundary. The operation:
 *          1. Converts pointer to numeric address
 *          2. Applies eya_addr_align_up()
 *          3. Converts back to void pointer
 *
 *          Example usage: Ensuring memory allocations meet alignment requirements
 *
 * @param ptr Pointer to align (may be unaligned)
 * @param align Alignment boundary (must be power of two)
 * @return void* Aligned pointer (always >= original pointer)
 *
 * @see eya_addr_align_up() For the underlying alignment implementation
 * @note
 * - Alignment must be power of two
 * - Null pointer input returns aligned null (0)
 * - Result always greater than or equal to input
 */
#define eya_ptr_align_up(ptr, align)                                                               \
    eya_addr_to_void(eya_addr_align_up(eya_ptr_to_uaddr(ptr), align))

/**
 * @def eya_ptr_align_down(ptr, align)
 * @brief Aligns a pointer down to the previous specified boundary
 * @details Adjusts the pointer to the nearest lower (or equal) memory address
 *          that matches the specified alignment boundary. The operation:
 *          1. Converts pointer to numeric address
 *          2. Applies eya_addr_align_down()
 *          3. Converts back to void pointer
 *
 *          Example usage: Finding start of aligned memory regions
 *
 * @param ptr Pointer to align (may be unaligned)
 * @param align Alignment boundary (must be power of two)
 * @return void* Aligned pointer (always <= original pointer)
 *
 * @see eya_addr_align_down() For the underlying alignment implementation
 * @note
 * - Alignment must be power of two
 * - Null pointer input returns aligned null (0)
 * - Result always less than or equal to input
 */
#define eya_ptr_align_down(ptr, align)                                                             \
    eya_addr_to_void(eya_addr_align_down(eya_ptr_to_uaddr(ptr), align))

#endif // EYA_PTR_UTIL_H
