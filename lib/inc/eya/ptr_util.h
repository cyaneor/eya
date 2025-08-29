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
 */

#ifndef EYA_PTR_UTIL_H
#define EYA_PTR_UTIL_H

#include "addr_util.h"
#include "nullptr.h"

/**
 * @def eya_ptr_cast(T, ptr)
 * @brief Casts a pointer to a pointer of type T.
 * @param T Target type (without pointer)
 * @param ptr Pointer to cast
 * @return Pointer of type T*
 */
#define eya_ptr_cast(T, ptr) eya_type_cast(T *, ptr)

/**
 * @def eya_ptr_ccast(T, ptr)
 * @brief Casts a pointer to a const pointer of type T.
 * @param T Target type (without const or pointer)
 * @param ptr Pointer to cast
 * @return Const pointer of type const T*
 */
#define eya_ptr_ccast(T, ptr) eya_ptr_cast(const T, ptr)

/**
 * @def eya_ptr_rcast(T, ptr)
 * @brief Pointer-specific reinterpret cast macro
 * @param T Target pointer type (e.g., int*, void*)
 * @param ptr Pointer value to cast
 * @return Casted pointer of type T
 * @note This macro is defined in terms of eya_reinterpret_cast
 * @see eya_reinterpret_cast
 */
#define eya_ptr_rcast(T, ptr) eya_reinterpret_cast(T *, ptr)

/**
 * @def eya_ptr_deref(T, ptr)
 * @brief Dereferences a pointer cast to type T*
 * @param T Target type (without pointer)
 * @param ptr Pointer to cast and dereference
 * @return Lvalue reference of type T
 * @note Type-safe combination of pointer cast and dereference
 * @warning Caller must ensure pointer validity and proper alignment
 * @see eya_ptr_cast()
 */
#define eya_ptr_deref(T, ptr) (*eya_ptr_cast(T, ptr))

/**
 * @def eya_ptr_is_null(ptr)
 * @brief Checks if a pointer is null
 * @param ptr Pointer to check
 * @return true if pointer is nullptr, false otherwise
 */
#define eya_ptr_is_null(ptr) ((ptr) == nullptr)

/**
 * @def eya_ptr_to_uaddr(ptr)
 * @brief Converts any pointer to an unsigned address type (eya_uaddr_t)
 * @param ptr Pointer to convert
 * @return Converted value of type eya_uaddr_t
 */
#define eya_ptr_to_uaddr(ptr) eya_reinterpret_cast(eya_uaddr_t, ptr)

/**
 * @def eya_ptr_to_saddr(ptr)
 * @brief Converts any pointer to a signed address type (eya_saddr_t)
 * @param ptr Pointer to convert
 * @return Converted value of type eya_saddr_t
 */
#define eya_ptr_to_saddr(ptr) eya_reinterpret_cast(eya_saddr_t, ptr)

/**
 * @def eya_ptr_sdiff(ptr1, ptr2)
 * @brief Calculates the signed difference between two pointers
 * @param ptr1 First pointer
 * @param ptr2 Second pointer
 * @return Signed difference between pointers as eya_saddr_t
 */
#define eya_ptr_sdiff(ptr1, ptr2) eya_addr_diff(eya_ptr_to_saddr(ptr1), eya_ptr_to_saddr(ptr2))

/**
 * @def eya_ptr_udiff(ptr1, ptr2)
 * @brief Calculates the unsigned difference between two pointers
 * @param ptr1 First pointer
 * @param ptr2 Second pointer
 * @return Unsigned difference between pointers as eya_uaddr_t
 */
#define eya_ptr_udiff(ptr1, ptr2) eya_addr_diff(eya_ptr_to_uaddr(ptr1), eya_ptr_to_uaddr(ptr2))

/**
 * @def eya_ptr_is_aligned(ptr, align)
 * @brief Checks if a pointer is aligned to the specified boundary
 * @param ptr Pointer to check
 * @param align Alignment boundary to check against
 * @return true if the pointer is aligned, false otherwise
 */
#define eya_ptr_is_aligned(ptr, align) eya_addr_is_aligned(eya_ptr_to_uaddr(ptr), align)

/**
 * @def eya_ptr_ranges_no_overlap(r1_begin, r2_begin, r2_end)
 * @brief Checks if two pointer ranges do not overlap
 * @param r1_begin Beginning of first range
 * @param r2_begin Beginning of second range
 * @param r2_end End of second range
 * @return true if ranges do not overlap, false otherwise
 */
#define eya_ptr_ranges_no_overlap(r1_begin, r2_begin, r2_end)                                      \
    (((r1_begin) <= (r2_begin)) || ((r2_end) <= (r1_begin)))

/**
 * @def eya_ptr_ranges_is_overlap(r1_begin, r2_begin, r2_end)
 * @brief Checks if two pointer ranges overlap
 * @param r1_begin Beginning of first range
 * @param r2_begin Beginning of second range
 * @param r2_end End of second range
 * @return true if ranges overlap, false otherwise
 */
#define eya_ptr_ranges_is_overlap(r1_begin, r2_begin, r2_end)                                      \
    (!eya_ptr_ranges_no_overlap(r1_begin, r2_begin, r2_end))

/**
 * @def eya_ptr_add_by_offset_unsafe(T, ptr, offset)
 * @brief Adds an offset to a pointer without safety checks (unsafe operation)
 * @param T Target pointer type
 * @param ptr Base pointer to offset from
 * @param offset Unsigned offset to add (in bytes)
 * @return T* pointer at the calculated address
 * @warning Unsafe operation without validation of pointer validity,
 *          offset bounds, or overflow conditions
 */
#define eya_ptr_add_by_offset_unsafe(T, ptr, offset)                                               \
    eya_addr_to_ptr(T, eya_math_add(eya_ptr_to_uaddr(ptr), offset))

/**
 * @def eya_ptr_sub_by_offset_unsafe(T, ptr, offset)
 * @brief Subtracts an offset from a pointer without safety checks (unsafe operation)
 * @param T Target pointer type
 * @param ptr Base pointer to offset from
 * @param offset Unsigned offset to subtract (in bytes)
 * @return T* pointer at the calculated address
 * @warning Unsafe operation without validation of pointer validity,
 *          offset bounds, or underflow conditions
 */
#define eya_ptr_sub_by_offset_unsafe(T, ptr, offset)                                               \
    eya_addr_to_ptr(T, eya_math_sub(eya_ptr_to_uaddr(ptr), offset))

/**
 * @def eya_ptr_add_by_offset(T, ptr, offset)
 * @brief Safely adds an offset to a pointer with null-checking
 * @param T Target pointer type
 * @param ptr Base pointer to offset from (may be null)
 * @param offset Unsigned offset to add (in bytes)
 * @return T* pointer at the calculated address, or null if input was null
 * @note Performs null check before operation
 * @warning Still requires caution about offset magnitude and resulting address validity
 */
#define eya_ptr_add_by_offset(T, ptr, offset)                                                      \
    (eya_ptr_is_null(ptr) ? ptr : eya_ptr_add_by_offset_unsafe(T, ptr, offset))

/**
 * @def eya_ptr_sub_by_offset(T, ptr, offset)
 * @brief Safely subtracts an offset from a pointer with null-checking
 * @param T Target pointer type
 * @param ptr Base pointer to offset from (may be null)
 * @param offset Unsigned offset to subtract (in bytes)
 * @return T* pointer at the calculated address, or null if input was null
 * @note Performs null check before operation
 * @warning Still requires caution about offset bounds and resulting address validity
 */
#define eya_ptr_sub_by_offset(T, ptr, offset)                                                      \
    (eya_ptr_is_null(ptr) ? ptr : eya_ptr_sub_by_offset_unsafe(T, ptr, offset))

/**
 * @def eya_ptr_add_unsafe(T, ptr1, ptr2)
 * @brief Performs unsafe pointer addition (no bounds checking)
 * @param T Target pointer type
 * @param ptr1 Base pointer
 * @param ptr2 Pointer to convert to offset
 * @return T* result of addition
 * @warning Unsafe operation without null checking or overflow validation
 */
#define eya_ptr_add_unsafe(T, ptr1, ptr2)                                                          \
    eya_ptr_add_by_offset_unsafe(T, ptr1, eya_ptr_to_uaddr(ptr2))

/**
 * @def eya_ptr_sub_unsafe(T, ptr1, ptr2)
 * @brief Performs unsafe pointer subtraction (no bounds checking)
 * @param T Target pointer type
 * @param ptr1 Base pointer
 * @param ptr2 Pointer to convert to offset
 * @return T* result of subtraction
 * @warning Unsafe operation without null checking or underflow validation
 */
#define eya_ptr_sub_unsafe(T, ptr1, ptr2)                                                          \
    eya_ptr_sub_by_offset_unsafe(T, ptr1, eya_ptr_to_uaddr(ptr2))

/**
 * @def eya_ptr_add(T, ptr1, ptr2)
 * @brief Safer pointer addition with null checking
 * @param T Target pointer type
 * @param ptr1 Base pointer (may be null)
 * @param ptr2 Pointer to convert to offset
 * @return T* result or null if ptr1 was null
 * @note Performs null check before operation
 */
#define eya_ptr_add(T, ptr1, ptr2) eya_ptr_add_by_offset(T, ptr1, eya_ptr_to_uaddr(ptr2))

/**
 * @def eya_ptr_sub(T, ptr1, ptr2)
 * @brief Safer pointer subtraction with null checking
 * @param T Target pointer type
 * @param ptr1 Base pointer (may be null)
 * @param ptr2 Pointer to convert to offset
 * @return T* result or null if ptr1 was null
 * @note Performs null check before operation
 */
#define eya_ptr_sub(T, ptr1, ptr2) eya_ptr_sub_by_offset(T, ptr1, eya_ptr_to_uaddr(ptr2))

/**
 * @def eya_ptr_align_up(T, ptr, align)
 * @brief Aligns a pointer up to the next specified boundary
 * @param T Target pointer type
 * @param ptr Pointer to align (may be unaligned)
 * @param align Alignment boundary (must be power of two)
 * @return T* Aligned pointer (always >= original pointer)
 * @note Alignment must be power of two
 * @see eya_addr_align_up()
 */
#define eya_ptr_align_up(T, ptr, align)                                                            \
    eya_add_to_ptr(T, eya_addr_align_up(eya_ptr_to_uaddr(ptr), align))

/**
 * @def eya_ptr_align_down(ptr, align)
 * @brief Aligns a pointer down to the previous specified boundary
 * @param ptr Pointer to align (may be unaligned)
 * @param align Alignment boundary (must be power of two)
 * @return void* Aligned pointer (always <= original pointer)
 * @note Alignment must be power of two
 * @see eya_addr_align_down()
 */
#define eya_ptr_align_down(ptr, align)                                                             \
    eya_add_to_ptr(T, eya_addr_align_down(eya_ptr_to_uaddr(ptr), align))

#endif // EYA_PTR_UTIL_H
